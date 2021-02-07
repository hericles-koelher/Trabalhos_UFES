<?php

namespace Aluno;

use Zend\Router\Http\Segment;

return [
    'router' => [
        'routes' => [
            'aluno' => [
                'type'    => Segment::class,
                'options' => [
                    'route' => '/aluno[/:action[/:id]]',
                    'constraints' => [
                        'action' => '[a-zA-Z][a-zA-Z0-9_-]*',
                        'id'     => '[0-9]+',
                    ],
                    'defaults' => [
                        'controller' => Controller\AlunoController::class,
                        'action'     => 'index',
                    ],
                ],
            ],
        ],
    ],

    'view_manager' => [
        'template_path_stack' => [
            'aluno' => __DIR__ . '/../view',
        ],
    ],

    'db' => [
        'driver' => 'Pdo_Mysql',
        'database' => 'Zend',
        'username' => 'Inccubus',
        'password' => 'Inccubus69',
        'hostname' => 'localhost',
    ],
];