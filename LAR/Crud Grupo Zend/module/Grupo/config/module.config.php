<?php

namespace Grupo;

use Zend\Router\Http\Segment;

return [
    'router' => [
        'routes' => [
            'grupo' => [
                'type'    => Segment::class,
                'options' => [
                    'route' => '/grupo[/:action[/:id]]',
                    'constraints' => [
                        'action' => '[a-zA-Z][a-zA-Z0-9_-]*',
                        'id'     => '[0-9]+',
                    ],
                    'defaults' => [
                        'controller' => Controller\GrupoController::class,
                        'action'     => 'index',
                    ],
                ],
            ],
        ],
    ],
    'view_manager' => [
        'template_path_stack' => [
            'grupo' => __DIR__ . '/../view',
        ],
    ],
    'db' => [
        'driver' => 'Pdo_Mysql',
        'database' => 'CRUD_Grupo',
        'username' => 'root',
        'password' => 'Hericles1234',
        'hostname' => 'MySQL_Server',
    ],
];