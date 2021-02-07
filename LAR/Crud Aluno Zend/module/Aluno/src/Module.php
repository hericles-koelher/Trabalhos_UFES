<?php

namespace Aluno;

use Zend\ModuleManager\Feature\ConfigProviderInterface;
use Zend\Db\Adapter\AdapterInterface;
use Zend\Db\ResultSet\ResultSet;
use Zend\Db\TableGateway\TableGateway;

class Module implements ConfigProviderInterface
{
    public function getConfig()
    {
        return include __DIR__ . '/../config/module.config.php';
    }

    //Basicamente abaixo estou indicando para o service manager como criar algumas classes
    //que irei utilizar, assim posso somente chama-las sem me preocupar com suas dependencias
    //OBS: Achei uma merda fazer o AlunoTableGateway aqui, acredito que seria melhor ter uma classe
    //em um arquivo proprio para isso
    public function getServiceConfig(){
        return [
            'factories' => [
                Model\AlunoTable::class => function($container) {
                    $tableGateway = $container->get(Model\AlunoTableGateway::class);
                    return new Model\AlunoTable($tableGateway);
                },
                Model\AlunoTableGateway::class => function ($container) {
                    $dbAdapter = $container->get(AdapterInterface::class);
                    $resultSetPrototype = new ResultSet();
                    $resultSetPrototype->setArrayObjectPrototype(new Model\Aluno());
                    return new TableGateway('Alunos', $dbAdapter, null, $resultSetPrototype);
                },
            ],
        ];
    }

    public function getControllerConfig(){
        return [
            'factories' => [
                Controller\AlunoController::class => function($container){
                    return new Controller\AlunoController($container->get(Model\AlunoTable::class));
                }
            ]
        ];
    }
}