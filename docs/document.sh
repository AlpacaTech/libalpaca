git whatchanged > log.txt
python3 cleanup.py log.txt index.html
python -m json.tool log.json
