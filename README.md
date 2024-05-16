# Asservissement d'une balle sur un plan incliné
Ce dépôt fournit les fichiers permettant de réaliser l'asservissement d'une balle sur un plan incliné en utilisant un corecteur PID. 

La balle roule sur deux axes en aluminium dont l'inclinaison est réglée par un système de leviers relié à un servomoteur standard. La position de la balle est déterminée par un capteur de distance VL53L0X, que l'on peut trouver monté sur une carte par exemple [ici](https://www.amazon.fr/gp/product/B086TSKJBT/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1). 

L'asservissement est réalisé par un Arduino Uno. 

| PIN Arduino | Description    |
| ----------- | -------------- |
| 5           | Impulsion servo|
| A0          | Potentiomètre 0|
| A1          | Potentiomètre 1|
| A2          | Potentiomètre 2|
