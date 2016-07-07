<?php
require 'Slim/Slim.php';

\Slim\Slim::registerAutoloader();
$app = new \Slim\Slim();
$app = \Slim\Slim::getInstance();

$app->get('/salons', 'getSalons');

$app->run();

function getSalons() {
    $sql = "select * FROM salons";
    try {
        $db = getConnection();
        $stmt = $db->query($sql);
        $wines = $stmt->fetchAll(PDO::FETCH_OBJ);
        $db = null;
        echo json_encode($wines);
    } catch(PDOException $e) {
        echo '{"error":{"text":'. $e->getMessage() .'}}';
    }
}
/*function addUser() {
    $request = Slim::getInstance()->request();
    $user = json_decode($request->getBody());
    $sql = "INSERT INTO users (username, first_name, last_name, address) VALUES (:username, :first_name, :last_name, :address)";
    try {
        $db = getConnection();
        $stmt = $db->prepare($sql);
        $stmt->bindParam("username", $user->username);
        $stmt->bindParam("first_name", $user->first_name);
        $stmt->bindParam("last_name", $user->last_name);
        $stmt->bindParam("address", $user->address);
        $stmt->execute();
        $user->id = $db->lastInsertId();
        $db = null;
        echo json_encode($user);
    } catch(PDOException $e) {
        echo '{"error":{"text":'. $e->getMessage() .'}}';
    }
}*/
function getConnection() {
    $dbhost="127.0.0.1";
    $dbuser="root";
    $dbpass="kartusaspass";
    $dbname="hairdressers";
    $dbh = new PDO("mysql:host=$dbhost;dbname=$dbname", $dbuser, $dbpass);
    $dbh->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    return $dbh;
}