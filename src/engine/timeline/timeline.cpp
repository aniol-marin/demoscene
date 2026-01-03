#include "timeline.h"

#include <algorithm>
#include <exception>
#include <memory>
#include <stdexcept>
#include <vector>
#include <iostream>

namespace MoleDemo
{
    using namespace mole_def;

    milliseconds timeSinceStart;
    milliseconds duration;

    bool confirm_is_done()
    {
        return true;
    }

    bool check_song_end()
    {
        return timeSinceStart > duration;
    }

    Event::Event(Timestamp time, Renderables renderables) :
      time(time),
      renderables(renderables),
      background(),
      foreground(),
      isDone(confirm_is_done),
      instantaneous(true),
      transition()
    {
    }

    Event::Event(Timestamp time, Renderable* background, Renderable* foreground, TransitionType transitionType) :
      time(time),
      renderables(),
      background(background),
      foreground(foreground),
      instantaneous(false),
      isDone(check_song_end),
      transition()
    {
        renderables.push_back(background);
        renderables.push_back(foreground);

        delete transition;

        switch (transitionType)
        {
            case mole_def::TRANSITION_TYPE_FADE:
            {
                Transition* transition = new Fade(time);
                transition->Bind(background, foreground);
                break;
            }
            default:
                transition = NULL;
                break;
        }
    }

    bool Event::Done(milliseconds deltaTime)
    {
        return isDone();
    }

    void Event::Update(permille intensity, permille deltaTime)
    {
        timeSinceStart += deltaTime;

        if (!instantaneous)
        {
            transition->Update(intensity, deltaTime);
        }
        UpdateLayers(intensity, deltaTime);
    }

    void Event::UpdateLayers(permille i, permille d)
    {
        for (Renderables::iterator r = renderables.begin(); r != renderables.end(); ++r)
        {
            (*r)->Update(i, d);
        }
    }

    Renderables Event::GetRenderables()
    {
        Renderables active = Renderables();
        if (!instantaneous)
        {
            if (!isDone())
            {
                active.push_back(transition);
            }
            else
            {
                active.push_back(foreground);
            }
        }
        else
        {
            active = renderables;
        }
        return active;
    }

    bool Event::TriggerReached(seconds current)
    {
        return current >= time.start;
    }

    Timeline::Timeline(Timer& timer,
                       Program& program,
                       Cycle& cycle,
                       SoundManager& sound,
                       Screen& screen,
                       const std::string& project) :
      currentEvent(NULL),
      timer(timer),
      program(program),
      cycle(cycle),
      sound(sound),
      screen(screen),
      project(project),
      renderables()
    {
    }

    void Timeline::Init()
    {
        if (initialized)
        {
            throw std::runtime_error("trying to initialize timeline twice");
        }

        initialized = true;
    }

    void Timeline::Finalize()
    {
        if (!initialized)
        {
            throw std::runtime_error("trying to finalize timeline twice");
        }

        initialized = false;
    }

    void Timeline::UpdateRenderables(Renderables newLayers)
    {
        Renderables* oldLayers = &renderables;

        // unload previously loaded effects (no longer needed)
        for (Renderables::iterator oldLayer = renderables.begin(); oldLayer != renderables.end(); ++oldLayer)
        {
            Renderables::iterator unused = std::find(newLayers.begin(), newLayers.end(), *oldLayer);
            if (unused != newLayers.end())
            {
                // TO DO really would need some refactor...
                Renderable* renderable(*unused);
                Loadable* loadable(reinterpret_cast<Loadable*>(renderable));
                loadable->Unload();
            }
        }

        // load previously unloaded effects
        for (Renderable* newLayer = *newLayers.begin(); newLayer != *newLayers.end(); ++newLayer)
        {
            Renderables::iterator unloaded = std::find(oldLayers->begin(), oldLayers->end(), newLayer);
            if (unloaded == oldLayers->end())
            {
                // TO DO really would need some refactor...
                Renderable* renderable(*unloaded);
                Loadable* loadable(reinterpret_cast<Loadable*>(renderable));
                loadable->Load("");
            }
        }

        renderables = newLayers;
        cycle.SetRenderables(renderables);
    }

    void Timeline::HandleTimeline()
    {
        if (currentEvent != NULL)
        {
            if (!currentEvent->Done(timer.GetDeltaTime()))
            {

                throw std::runtime_error(" timeline handling deactivated");
                currentEvent->Update(sound.GetCurrentIntensity(), timer.GetDeltaTime());
            }
            else
            {
                UpdateRenderables(currentEvent->GetRenderables());
                currentEvent = NULL;
                events.pop();
            }
        }
        else if (!events.empty() && events.front()->TriggerReached(timer.GetTime()))
        {
            currentEvent = events.front();
            UpdateRenderables(currentEvent->GetRenderables());
            cycle.SetRenderables(renderables);
        }
    }

    Layer* Timeline::CreateLayer(BlendMode mode, Effect* effect)
    {
        Layer* layer(new Layer(mode, effect));
        availableLayers.push_back(layer);
        return layer;
    }

    /*
    std::unique_ptr<Event> Timeline::CreateEvent(Timestamp time, Renderables renderables)
    {
        return std::move(std::make_unique<Event>(time, renderables));
    }

    std::unique_ptr<Event> Timeline::CreateEvent(Timestamp time,
                                                 Renderable* background,
                                                 Renderable* foreground,
                                                 TransitionType transition)
    {
        return std::move(std::make_unique<Event>(time, background, foreground, transition));
    }
     */

    /*
       Solid* Timeline::CreateSolid(const pugi::xml_node node)
       {
       mole::pugi_wrapper::node<Solid> deserialized{ node, &timer, &screen };
       std::unique_ptr<Solid> p_effect{ std::make_unique<Solid>(deserialized.deserialize()) };
       Solid* effect{ p_effect.get() };
       availableEffects.push_back(std::move(p_effect));
       return effect;
       }
*/

    void Timeline::Load(const std::string& content)
    {
        if (!initialized)
        {
            throw std::runtime_error("trying to load an uninitialized timeline");
        }
        if (loaded)
        {
            throw std::runtime_error("trying to load a timeline twice");
        }

        LoadInternal(content);
        loaded = true;
    }
    void Timeline::Unload()
    {
        if (!initialized)
        {
            throw std::runtime_error("trying to unload an uninitialized timeline");
        }
        if (!loaded)
        {
            throw std::runtime_error("trying to unload a timeline twice");
        }

        for (EffectsRepository::iterator effect = availableEffects.begin(); effect != availableEffects.end(); ++effect)
        {
            (*effect)->Unload();
        }
        loaded = false;
    }
    void Timeline::Start()
    {
        if (!loaded)
        {
            throw std::runtime_error("truing to start an unloaded timeline");
        }
        if (started)
        {
            throw std::runtime_error("truing to start a timeline twice");
        }

       timer.SetEndTime(sound.GetMusicDuration());
        started = true;
    }
    void Timeline::Stop()
    {
        if (!started)
        {
            throw std::runtime_error("trying to stop an unstarted timeline");
        }

        started = false;
    }

    void Timeline::LoadInternal(const std::string& content)
    {
        // TODO argument forwarding on CreateEffect template

        // Effects
        /*
        // TODO load project from JSON
        pugi::xml_node solid1_node{};
        solid1_node.append_attribute("color").as_uint(black);
        Solid* solid1{ CreateSolid(solid1_node) };

        pugi::xml_node solid2_node{};
        solid2_node.append_attribute("color").as_uint(black);
        Solid* solid2{ CreateSolid(solid2_node) };

        Gradient* gradient1{ CreateEffect<Gradient>() };
        gradient1->SetColors(white, black, black, white);

        Gradient* gradient2{ CreateEffect<Gradient>() };
        gradient2->SetColors(white, black, white, black);

        Gradient* gradient3{ CreateEffect<Gradient>() };
        gradient3->SetColors(white, red, green, blue);

        Gradient* gradient4{ CreateEffect<Gradient>() };
        gradient4->SetColors(black, teal, magenta, orange);

        // Effects with custom settings
        channel low{ 30 };
        channel high{ 100 };
        Color skyN{ low, low, high, saturated };
        Color skyS{ low, low, clear, saturated };
        Gradient* gradient5{ CreateEffect<Gradient>() };
        gradient5->SetColors(skyN, skyN, skyS, skyS);

        ChessBoard* chessBoard{ CreateEffect<ChessBoard>() };
        chessBoard->Set(0x4DA424, 0xA42479, 8);

        RandomNoise* noise{ CreateEffect<RandomNoise>() };
        noise->Set(red, black, 128);

        // Effects with custom textures
        std::unique_ptr<Texturable> tunnelGradientTexture = std::unique_ptr<Texturable>(std::make_unique<Gradient>());
        Gradient& TGT = *static_cast<Gradient*>(tunnelGradientTexture.get());
        TGT.SetColors(blue, teal, red, green);
        Tunel* tunnelGradient = CreateEffect<Tunel>();
        tunnelGradient->AssignTexture(std::move(tunnelGradientTexture), 0);

        std::unique_ptr<Texturable> tunnelChessTexture = std::make_unique<ChessBoard>();
        ChessBoard& TCT = *static_cast<ChessBoard*>(tunnelChessTexture.get());
        TCT.Set(yellow, orange, 16);
        Tunel* tunnelChess = CreateEffect<Tunel>();
        tunnelChess->AssignTexture(std::move(tunnelChessTexture), 0);

        std::unique_ptr<Texturable> tunnelDirtyTexture = std::make_unique<RandomNoise>();
        RandomNoise& TDT = *static_cast<RandomNoise*>(tunnelDirtyTexture.get());
        TDT.Set(concrete, black, 32);
        Tunel* tunnelDirty = CreateEffect<Tunel>();
        tunnelDirty->AssignTexture(std::move(tunnelDirtyTexture), 0);
        */

        // Layers
        Layer* stars(CreateLayer(mole_def::BLEND_MODE_ALPHABLEND, CreateEffect<Stars>()));
	/*
        Layer* solids(CreateLayer(mole_def::BLEND_MODE_ALPHABLEND, CreateEffect<Solid>()));
        Layer* plasma{ CreateLayer(BlendMode::Override, CreateEffect<Plasma>()) };
        Layer* fire{ CreateLayer(BlendMode::Override, CreateEffect<Fire>()) };
        Layer* black{ CreateLayer(BlendMode::Override, solid1) };
        Layer* white{ CreateLayer(BlendMode::Override, solid2) };
        Layer* verticalGradient{ CreateLayer(BlendMode::Override, gradient1) };
        Layer* diagonalGradient{ CreateLayer(BlendMode::Override, gradient2) };
        Layer* primaries{ CreateLayer(BlendMode::Override, gradient3) };
        Layer* secondaries{ CreateLayer(BlendMode::Override, gradient4) };
        Layer* sky{ CreateLayer(BlendMode::Override, gradient5) };
        Layer* wheel{ CreateLayer(BlendMode::Override, CreateEffect<Wheel>()) };
        Layer* tunnelSmooth{ CreateLayer(BlendMode::Override, tunnelGradient) };
        Layer* tunnelEpilepsy{ CreateLayer(BlendMode::Override, tunnelChess) };
        Layer* chess{ CreateLayer(BlendMode::Override, chessBoard) };
        Layer* sonicPollution{ CreateLayer(BlendMode::Override, noise) };
        Layer* sanitaryPollution{ CreateLayer(BlendMode::Override, tunnelDirty) };

    */
        // Layers initialization
        for (EffectsRepository::iterator effect = availableEffects.begin(); effect != availableEffects.end(); ++effect)
        {
            (*effect)->Load();
        }

        renderables.push_back(stars);
        /*
            events.push(std::make_unique<Event>(Timestamp{ 5, 2000 }, stars, solids, TransitionType::Fade));
                 events.push(std::make_unique<Event>(Timestamp{ 5, 2000 }, stars, sanitaryPollution,
           TransitionType::Fade)); events.push(std::make_unique<Event>(Timestamp{ 31, 2000 }, fire, wheel,
           TransitionType::Fade)); events.push(std::make_unique<Event>(Timestamp{ 40, 2000 }, wheel, black,
           TransitionType::Fade)); events.push(std::make_unique<Event>(Timestamp{ 43, 2000 }, black, white,
           TransitionType::Fade)); events.push(std::make_unique<Event>(Timestamp{ 45, 2000 }, white, verticalGradient,
           TransitionType::Fade)); events.push(std::make_unique<Event>( Timestamp{ 47, 2000 }, verticalGradient,
           diagonalGradient, TransitionType::Fade)); events.push(std::make_unique<Event>(Timestamp{ 49, 4000 },
           diagonalGradient, primaries, TransitionType::Fade)); events.push(std::make_unique<Event>(Timestamp{ 53, 3000
           }, primaries, secondaries, TransitionType::Fade)); events.push(std::make_unique<Event>(Timestamp{ 56, 512 },
           secondaries, chess, TransitionType::Fade)); events.push(std::make_unique<Event>(Timestamp{ 58, 512 }, chess,
           sonicPollution, TransitionType::Fade)); events.push(std::make_unique<Event>(Timestamp{ 65, 10000 },
           sonicPollution, plasma, TransitionType::Fade)); events.push(std::make_unique<Event>(Timestamp{ 77, 1000 },
           plasma, black, TransitionType::Fade)); events.push(std::make_unique<Event>(Timestamp{ 78, 1000 }, black, sky,
                TransitionType::Fade)); events.push(std::make_unique<Event>(Timestamp{ 79, 0 }, Renderables{ sky, stars
           })); events.push(std::make_unique<Event>(Timestamp{ 90, 0 }, Renderables{ tunnelSmooth }));
                 events.push(std::make_unique<Event>(Timestamp{ 100, 0 }, Renderables{ tunnelEpilepsy }));
                 events.push(std::make_unique<Event>(Timestamp{ 105, 0 }, Renderables{ sanitaryPollution }));
                 events.push(std::make_unique<Event>(Timestamp{ 110, 1000 }, sanitaryPollution, wheel,
                TransitionType::Fade)); events.push(std::make_unique<Event>(Timestamp{ 300, 10000 }, wheel, black,
                TransitionType::Fade));

        UpdateRenderables(renderables);
	*/
    }

    void Timeline::Update()
    {
	    std::cerr //
		    << "\n" //
		    << "\n" //
		    << "##########################################################\n" //
		    << "## Timeline update temporarily disabled. Aborting loop. ##\n" //
		    << "##########################################################\n" //
		    << "\n" //
		    << "\n" //
		    ;	
	program.SetStatus(mole_def::PROGRAM_TERMINATE_OK);

	HandleTimeline();

        cycle.PollEvents();
        cycle.Update(sound.GetCurrentIntensity());
	/*
        cycle.Draw();
        cycle.Synch();
	*/
    }
}
