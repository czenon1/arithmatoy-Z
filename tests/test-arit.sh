#! usr/bin/env/ bash

python -m pytest test_arithmatoy.py -k test_add
python -m pytest test_arithmatoy.py -k test_sub
python -m pytest test_arithmatoy.py -k test_mul
python -m pytest test_arithmatoy.py -k run_tests
python -m pytest test_arithmatoy.py -k dec_to_base