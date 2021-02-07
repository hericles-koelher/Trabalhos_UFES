<?php

namespace Grupo\Controller;

use Grupo\Model\Grupo;
use Grupo\Model\NameValidator;
use Zend\Mvc\Controller\AbstractActionController;
use Zend\View\Model\ViewModel;
use Grupo\Model\GrupoTable;

class GrupoController extends AbstractActionController
{
    private $table;

    public function __construct(GrupoTable $grupoTable)
    {
        $this->table = $grupoTable;
    }

    public function indexAction()
    {
        return new ViewModel(['grupos' => $this->table->fetchAll()]);
    }

    public function addAction()
    {
        if(!$this->getRequest()->isPost()){
            return new ViewModel();
        }

        $val_name = new NameValidator();

        $data = new Grupo();
        $data->exchangeArray($this->params()->fromPost());

        if(!$val_name->isValid($data->nome)){
            throw new \RuntimeException('Nome Inválido!');
        }

        $this->table->saveGrupo($data);

        $this->redirect()->toRoute('grupo');

    }

    public function editAction()
    {
        $id = (int) $this->params()->fromRoute('id',0);

        if($id === 0){
            $this->redirect()->toRoute('grupo',['action' => 'add']);
        }

        if(!$this->getRequest()->isPost()){
            /*o id é passado aqui para que possa ser reenviado da proxima vez que a action for executada,
            do contrario terei id = 0, mesmo que esteja editando um grupo já existente*/
            return new ViewModel(['data' => $this->table->getGrupo($id), 'id' => $id]);
        }

        $nome = $this->params()->fromPost()['nome'];

        $val_name = new NameValidator();

        if(!$val_name->isValid($nome)){
            throw new \RuntimeException('Nome Inválido!');
        }

        $data = new Grupo();
        $data->exchangeArray(['id' => $id, 'nome' => $nome]);

        $this->table->saveGrupo($data);

        $this->redirect()->toRoute('grupo');

    }

    public function deleteAction()
    {
        $id = (int) $this->params()->fromRoute('id',0);

        if($id === 0){
            $this->redirect()->toRoute('grupo',['action' => 'add']);
        }

        if(!$this->getRequest()->isPost()){
            //o id é passado aqui para que possa ser reenviado da proxima vez que a action for executada,
            //do contrario terei id = 0, mesmo que esteja editando um grupo já existente
            return new ViewModel(['data' => $this->table->getGrupo($id), 'id' => $id]);
        }

        $this->table->deleteGrupo($id);

        $this->redirect()->toRoute('grupo');

    }

}