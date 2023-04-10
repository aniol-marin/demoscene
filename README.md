Enllaç al repositori
	https://gitlab.com/amarinat/demoscene-2023

Presentació
	La meva proposta resol els següents punts de l'enunciat:
	* Utilitza els mètodes mínims de SDL2 per controlar els píxels al 100 (i Raylib Audio per gestionar el so)
	* Presenta un total de 5 efectes
	* Afegeix i sincronitza els efectes amb la música
	* Permet l'ús de transicions i renderitzat de múltiples capes
	* Permet l'actualització dels efectes independentment del framerate
	* Permet l'ajust d'alguns dels efectes visuals en base al so
		** Stars canvia la saturació dels colors segons la intensitat sonora
		** Fire genera un nombre i extensió de flama diferent segons la intensitat sonora
		** Plasma ajusta la paleta de colors a la intensitat sonora
	* Aplica a bastament algorismes i recursos de C++
	* Intenta aplicar clean code (més basat en l'estil de Stroustrup que en el de Martin)
	* Separa la càrrega i el precàlcul del renderitzat imprescindible en temps real
	* Permet la sincronia total de so i imatge (actualment amb resolució d'un segon, però es podria augmentar fàcilment la resolució)
	
	No resol en canvi els punts següents:
	* No genera algorismes propis (excepte els efectes més bàsics i la modificació dels efectes proporcionats)
	* Els efectes no estan plenament optimitzats
	* El framerate pateix caigudes importants
	* No aporta transicions variades (tot i que el sistema està preparat per suportar-les)
	* El conjunt final no és visualment agradable
	
Procés creatiu
	La tria de la música ha sigut el condicionant principal, ja que tenia moltes ganes de generar-ne un videoclip; el ritme pausat és el que dicta l'estètica (tot i que irònicament la base rítmica combina jazz, trap, i poliritmes inspirats en progressive rock). Tinc moltíssimes idees sobre com voldria que quedés la demo final. El degradat final per exemple hauria de ser un efecte per sí sol (Skybox d'una posta de sol). El plasma el vull fer amb un precàlcul de vector noise. La classe Color està preparada per permetre hue shift eficient. Per no començar a parlar dels efectes i transicions que no he tingut temps ni de començar. La idea és que les escenes flueixin lliurement, per això he donat tanta importància a la crearió d'una línia de temps flexible (que de fet conceptualment hauria de permetre fins i tot el rebobinat, tot i que no està pràcticament implementat).
	
Com compilar
	Per poder compilar el projecte, cal tenir en compte el següent:
	* Cal utilitzar un compilador per C++20 o superior.
		en VSC,	Project Properties -> Configuration Properties -> General -> C++ Language Standard => ISO C++20 Standard (/std:c++20)
	* Tots els fitxers .ixx s'han de compilar com a interfície de mòdul 
		en VSC, Property Pages -> Configuration Properties -> C/C++ -> Advanced -> Compile As => Compile as C++ Module Code (/Interface)
	* Tots els fitxers .cpp s'han de compilar com a codi C++
		en VSC, Property Pages -> Configuration Properties -> C/C++ -> Advanced -> Compile As => Compile as C++ Code (/TP)
	* S'utilitzen com a dependències externes SDL2 i una versió modificada de Raylib Audio Standalone.
		al zip s'inclouen els fitxers .h, .lib i .dll per poder compilar, així com els projectes de VSC i els submòduls necessaris per recompilar des de la font
	* L'executable espera trobar un fitxer anomenat "molelofi.mp3" a la carpeta ./resources/
		al projecte de VSC 2022 es genera automàticament la còpia dels fitxers necessaris a les destinacions del fitxer de debug i del binari
		
		
Notes de programació
	* He utilitzat export type aliasing pels conceptes i build in types més adequats (en general std::~ i uint_fastXX_t respectivament)
	* He utilitzat export struct aliasing per forçar strong typing on m'ha sigut possible
	* No he utilizat ni una sola línia de preprocessador (excepte per incloure les llibreries de tercers.
	* L'absència de macros és intencionadament substituida per templates.
	* He intentat mantenir const correctness sempre que m'ha sigut possible, tot i que encara m'és difícil i crec que es pot millorar.
	* He utilitzat smart pointers i referències per separar ownership i ús
	* No s'ha utilitzat cap new ni delete (ni malloc/free, és clar), els únics raw pointers que s'han utilitzat són referències extretes amb unique_ptr.get().
	* He utilitzat C-style cast per conveniència, especialment en combinació amb inicialització incompatible amb  narrowing ({}). Per la resta he utilitzat static_cast o dynamic_cast

Organització del codi
	El codi està estructurat en tres namespaces, un de bàsic (MoleDemo) i dos com a wrappers per les llibreries de tercers (SDL i RAudio). Tot i que no s'estructura en capes, he intentat que cada fitxer s'encarregui d'un nivell o segment específic. Destaco els fitxers més importants:
		- main.cpp és una simple declaració del flux de l'aplicació
		- demo.ixx s'encarrega de la gestió de l'aplicació. Té molts imports simplement perquè s'encarrega de gestionar la inversió de control. Algunes de les variables privades no són necessàries, però no ho he vist a temps per netejar-ho abans de l'entrega.
		- timeline.ixx engloba la gestió dels events visuals, sense entrar en detalls de com executar-los.
		- render.ixx és on es troben les classes directament relacionades amb la manipulació5 de renderitzables (capes i transicions).
		- effects.ixx és un header pur, tal i com m'hauria agradat separar la resta de ixx de les respectives implementacions.
		- Effect.cpp, Stars.cpp, Fire.cpp... són les implementacions corresponents. Tots els effectes es basen en la classe abstracta Effect.
	Tot el codi propi està escrit en C++ modern. No he pogut aplicar RAII perquè no he tingut temps de completar la injecció de paràmetres amb el contenidor d'inversió de control, de manera que els constructors només s'han utilitzat per les dependències; per mantenir-ho simètric he separat tot el que m'ha sigut possible simètricament, a Init() / Finalize() i Load() / Unload().
	
Notes personals
	Estic prou content del que he aconseguit amb l'arquitectura de l'aplicació, així com amb la música (que vaig fer jo mateix fa uns anys). També estic prou content d'haver aconseguit un rendiment relativament bo amb un sistema complex i que utilitza les llibreries de suport d'una manera bastant bàsica (en especial la gestió dels modes de mescla de renderitzables i la gestió del temps, basats només en la standard library).
	Evidentment del que no estic gens content és del resultat obtingut, tot i que he sigut sempre conscient del biaix de dedicació en els diferents aspectesl
	
	Tinc clar que m'ha faltat temps per optimitzar el codi així com per afegir més efectes i polir els existents. També sóc plenament conscient que tenint en compte la base dels materials de referència he fet un treball molt just. Espero només que sigui suficient com per fer mitjana després amb la resta d'entregues, ja que la meva intenció és acabar el màster el més aviat possible i, tot i matricular-me d'una sola assignatura per semestre, no seria la primera vegada que tanco el curs en blanc per manca de temps.
	
	Espero sortir-me'n millor a la propera. En tot cas, m'ho he passat molt bé amb el que porto ja fet.
	
	Aniol
	Zagreb, 10/11 d'abril de 2023