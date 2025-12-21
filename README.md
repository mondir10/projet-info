C-WildWater
===========

Ce projet est une application en C permettant d’analyser un réseau hydraulique
à partir d’un fichier CSV.  
Il permet de calculer des histogrammes de volumes et les pertes (fuites) du réseau,
et de générer automatiquement des graphiques.

---

Prérequis
---------

Le projet est prévu pour être utilisé sous Linux ou WSL (Ubuntu recommandé).

Outils nécessaires :
- gcc
- make
- gnuplot

Installation sous Ubuntu / WSL :

sudo apt update
sudo apt install -y build-essential gnuplot


---

Fichier CSV
-----------

Le fichier CSV du réseau hydraulique n’est pas fourni dans le dépôt.

Avant toute utilisation :
1. placer le fichier CSV dans le dossier `data/`
2. renommer le fichier exactement :

water_network.dat

Chemin attendu :
data/water_network.dat

---

Compilation
-----------

Depuis la racine du projet :

make


Le binaire généré est :

wildwater_test


---

Utilisation
-----------

### Exécution complète automatique (recommandée)

Un script principal permet de compiler le projet, d’exécuter tous les calculs
et de générer les graphiques.

Rendre le script exécutable (une seule fois) :

chmod +x myScript.sh


Lancer le script :
./myScript.sh data/water_network.dat



---

### Exécution manuelle

Histogrammes :

./wildwater_test data/water_network.dat max
./wildwater_test data/water_network.dat src
./wildwater_test data/water_network.dat real

Calcul des pertes (fuites) du réseau :

./wildwater_test data/water_network.dat loss

Graphe complémentaire (TOP 10 MAX) :

Le graphique présentant les 10 plus grandes usines (volume MAX) est généré
à partir des données produites par la commande `max`, à l’aide de gnuplot :

gnuplot -e "INPUT='histo_max.dat'; OUTPUT='plots/histo_max_big.png'; TITLE='10 plus grandes usines (MAX)'; COUNT=10" plots/histo.gnuplot

---

Résultats
---------

Après exécution :
- des fichiers de données (`.dat`) sont générés à la racine du projet
- des graphiques (`.png`) sont générés dans le dossier `plots/`

Ces fichiers générés ne sont pas versionnés.

---

Nettoyage
---------

make clean


