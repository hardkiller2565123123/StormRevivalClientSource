============================================================
XFBIN NUCC PARSER
============================================================

- A binary parsing manual for XFBIN and NUCC-style assets, including page maps, chunk dispatch, validation, and
  viewer proof.

Code map
- AssetNuccDecoder, AssetModelViewer, FileParser helpers, XFBIN chunk tables, NUCC chunk bodies.

============================================================
Format Reality
============================================================

- XFBIN and NUCC data are structured binary formats.
- They are not flat byte streams.
- Page maps and chunk maps decide where real data lives.
- Chunk types decide how bodies are parsed.
- Offsets and counts must be validated.
- Useful geometry can live in primitive vertex or model hit style chunks.
- String tables and references matter.
- Unknown chunks should be skipped with warnings, not guessed.

============================================================
Parser Method
============================================================

- Validate header.
- Read counts with correct endianness.
- Resolve page map.
- Resolve chunk map.
- Validate every offset against file length.
- Dispatch by chunk type.
- Parse known bodies into typed structures.
- Collect warnings.
- Return assets, warnings, and errors.
- Render only validated data.

============================================================
Debug Signs
============================================================

- Exploded geometry suggests stride or coordinate mistakes.
- Invisible model suggests alpha or primitive lookup issues.
- Crash near file end suggests bad count or offset validation.
- Wrong names suggest string table indexing.
- Merged models suggest chunk grouping mistakes.
- Fallback visualization should be labeled as fallback.
- Source-only parser work should be marked unproven until sample-tested.
- A support file should include failing chunk type and offset.

============================================================
Practical Example
============================================================

- A good practical test for XFBIN NUCC PARSER starts by launching the correct game target, confirming the proxy
  loaded, checking the framework or diagnostics view, and then performing the smallest menu action connected to this
  topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Parser Lab
============================================================

- Validate header before reading tables.
- Read counts with the correct endian helper.
- Resolve page map before chunk bodies.
- Resolve chunk map before typed parsing.
- Validate offsets and sizes against file length.
- Dispatch by chunk type.
- Skip unknown chunks with warnings.
- Render only validated geometry.

============================================================
Parser Failure Signs
============================================================

- Exploded mesh suggests stride or coordinate interpretation errors.
- Invisible mesh suggests alpha or primitive lookup issues.
- Crash near file end suggests count or offset validation failure.
- Wrong names suggest string table indexing.
- Merged models suggest chunk grouping mistakes.
- Fallback visualization should be labeled as fallback.
- Source-only proof should say runtime sample still needed.
- Support should include failing chunk type and offset.

End of manual.
