<?php


namespace Grupo;

use Grupo\Controller\GrupoController;
use Grupo\Model\GrupoTable;
use Grupo\Model\Grupo;
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

    public function getServiceConfig(){
        return [
            'factories' => [
                Model\GrupoTable::class => function($container)
                {
                    $tableGateway = $container->get(Model\GrupoTableGateway::class);
                    return new GrupoTable($tableGateway);
                },

                Model\GrupoTableGateway::class => function($container)
                {
                    $dbAdapter = $container->get(AdapterInterface::class);
                    $resultSetPrototype = new ResultSet();
                    $resultSetPrototype->setArrayObjectPrototype(new Grupo());
                    return new TableGateway('Grupo', $dbAdapter, null, $resultSetPrototype);
                },
            ],
        ];
    }

    public function getControllerConfig(){
        return [
            'factories' => [
                Controller\GrupoController::class => function($container)
                {
                    $table = $container->get(Model\GrupoTable::class);
                    return new GrupoController($table);
                },
            ]
        ];
    }

}