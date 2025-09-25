FR :

<h2>Ceci est un projet système de location de voiture.</h2>

> Utilisation :
 
A partir de ce projet vous pourrez créer, modifier ou supprimer des voitures d'un système d'administration.

> BDD

Le fichier situé dans sql_lite/CarRental.db est une base de données avec les utilisateurs pré-enregistrés. 

Il vous suffira donc de :
- Soit le copier-coller dans le chemin suivant C:\sql_lite\\arRental.db pour pouvoir l'utiliser.
- Ou bien placer ce fichier dans le chemin de votre choix et corriger le chemin d'accès inscrit dans le fichier SqliteDatabase.h (variable "dir" en dessous de "dbname").

Un accès direct à la BDD SQLLite est disponible en entrant l'option 999 **une fois connecter en tant qu'administrateur**. A partir de cette option, des commandes sql peuvent être lû et exécuter directement depuis l'administration.

> Connexion

Les identifiants de connexion son les suivant : 

- username : Admin mdp : admin
-  username : User : mdp : user

Le niveau de privilège n'est pas le même pour chaque utilisateur (user : niveau 1, admin : niveau 2) ; les options disponibles variront donc en fonction du choix.


EN :

<h2>This project is a car rental system.</h2>

> Usage:

In this project, you will be able to view, create, modify, or delete cars in an administration system.

> Database

The file located at sql_lite/CarRental.db is a database with pre-registered users. 

In order to use it, all you need to do is :
- Either copy and paste the file at the following path: C:\sql_lite\CarRental.db.
- Or place this file wherever you like and update the path in the SqliteDatabase.h file (the "dir" variable).

Direct access to the SQLite database is available by entering option 999 **once logged in as an administrator**. From this option, SQL commands can be read and executed directly from the administration system.

> Login

The login credentials are as follows:

- username: Admin, password: admin
- username: User, password: user

The privilege level is not the same for each user (user: level 1, admin: level 2) ; meaning the available options will vary depending on the chosen user.
