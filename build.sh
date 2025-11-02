#!/bin/bash

python3 create_typ.py

python3 establish_links.py README_processed.md > README_processed_linked.md

typst compile main.typ

rm README_processed.md

rm README_processed_linked.md