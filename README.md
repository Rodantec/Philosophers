# Philosophers

Philosophers est un projet de synchronisation concurrente inspiré du problème des philosophes qui dînent (https://www.tutorialspoint.com/article/dining-philosophers-problem-dpp). Le but est de gérer plusieurs threads, des mutex et un suivi précis du temps afin d'éviter les collisions et de détecter la mort d'un philosophe.

## Objectif

Le programme doit simuler des philosophes qui :

- pensent
- prennent deux fourchettes
- mangent
- lachent les fourchettes
- dorment

Le projet impose aussi de surveiller le temps écoulé pour savoir si un philosophe meurt de faim, et d'arrêter proprement la simulation.

## Structure

- `main.c` : point d'entrée du programme
- `parsing.c` : validation et lecture des arguments
- `init.c` : initialisation de la table, des philosophes et des mutex
- `routine.c` : routine principale de chaque philosophe
- `monitor.c` : surveillance de l'état des philosophes
- `utils.c` et `utils1.c` : fonctions utilitaires
- `philo.h` : déclarations du projet

## Compilation

Depuis la racine du projet :

```bash
make
```

Cela génère l'exécutable `philo`.

## Commandes Makefile

- `make` : compile le projet
- `make clean` : supprime les fichiers objets
- `make fclean` : supprime les objets et l'exécutable `philo`
- `make re` : reconstruit le projet depuis zéro

## Lancement

Le programme attend les arguments suivants :

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Exemple :

```bash
./philo 5 800 200 200
```

Avec le nombre de repas obligatoire :

```bash
./philo 5 800 200 200 7
```

## Paramètres

- `number_of_philosophers` : nombre total de philosophes
- `time_to_die` : temps maximum sans manger avant de mourir
- `time_to_eat` : durée d'un repas
- `time_to_sleep` : durée du sommeil
- `number_of_times_each_philosopher_must_eat` : optionnel, nombre de repas requis pour terminer

## Fonctionnement

- chaque philosophe est exécuté dans un thread
- les fourchettes sont protégées par des mutex
- un thread de monitoring vérifie la mort des philosophes et la fin de simulation
- les messages sont sérialisés pour éviter un affichage mélangé

## Notes

- Le comportement exact dépend du respect des règles du sujet 42.