FR :

<h2>Ceci est un projet syst�me de location de voiture.</h2>

> Utilisation :
 
Ce projet permet de visualiser, cr�er, modifier ou supprimer des voitures d'un syst�me d'administration.

> BDD

Le fichier situ� dans sql_lite/CarRental.db est une base de donn�es avec les utilisateurs pr�-enregistr�s. 

Il vous suffira donc de :
- Soit cr�er un fichier situ� dans le chemin suivant C:\\sql_lite\\CarRental.db pour pouvoir l'utiliser.
- Ou bien placer ce fichier dans le chemin de votre choix et corriger le chemin d'acc�s inscrit dans le fichier SqliteDatabase.h (variable "dir" en dessous de "dbname").

Un acc�s direct � la BDD SQLLite est disponible en entrant l'option 999 **une fois connecter en tant qu'administrateur**. A partir de cette option, des commandes sql peuvent �tre l� et ex�cuter directement depuis l'administration.

> Connexion

Les identifiants de connexion son les suivant : 

- username : Admin mdp : admin
-  username : User : mdp : user

Le niveau de privil�ge n'est pas le m�me pour chaque utilisateur (user : niveau 1, admin : niveau 2) ; les options disponibles variront donc en fonction du choix.


EN :

<h2>This is a car rental system project.</h2>

> Usage:

This project allows you to view, create, modify, or delete cars in an administration system.

> Database

The file located at sql_lite/CarRental.db is a database with pre-registered users. 

You simply need to:
- Either create a file at the following path: C:\\sql_lite\\CarRental.db to use it.
- Or place this file wherever you like and update the path in the SqliteDatabase.h file (the "dir" variable below "dbname").

Direct access to the SQLite database is available by entering option 999 **once logged in as an administrator**. From this option, SQL commands can be read and executed directly from the administration system.

> Login

The login credentials are as follows:

- username: Admin, password: admin
- username: User, password: user

The privilege level is not the same for each user (user: level 1, admin: level 2); the available options will vary depending on the user.
