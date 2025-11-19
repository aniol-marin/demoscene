CALL cmake -Bbuild-artifacts -DCMAKE_RUNTIME_OUTPUT_DIRECTORY:PATH=. --preset=user --log-level=NOTICE
CALL cmake --build build-artifacts -t demoscene
CALL .\demoscene
