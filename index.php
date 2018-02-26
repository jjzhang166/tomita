<?php

require __DIR__ . '/vendor/autoload.php';

$result = [];
if (!empty($_POST['symptoms'])) {
    $p = new Tomita\TomitaParser(__DIR__ . '/tomita-parser/build/bin/tomita-parser', __DIR__ . '/tomita-parser/config/config.proto');
    $result = $p->run($_POST['symptoms']);
    //die(var_dump($result));
    $result = $result['facts'];
}

$loader = new Twig_Loader_Filesystem(__DIR__ . '/templates');
$twig = new Twig_Environment($loader, []);
$template = $twig->load('index.html');

echo $template->render(array('result' => $result));