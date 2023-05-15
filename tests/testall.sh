#! usr/bin/env/ bash

python -m pytest test_tp.py -k test_nombre_entier
python -m pytest test_tp.py -k test_successeur
python -m pytest test_tp.py -k test_addition
python -m pytest test_tp.py -k test_multiplication
python -m pytest test_tp.py -k test_facto_ite
python -m pytest test_tp.py -k test_facto_rec
python -m pytest test_tp.py -k test_fibo_rec
python -m pytest test_tp.py -k test_fibo_ite
python -m pytest test_tp.py -k test_golden_phi
python -m pytest test_tp.py -k test_sqrt5
python -m pytest test_tp.py -k test_pow
