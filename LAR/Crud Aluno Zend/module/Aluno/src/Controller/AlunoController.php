<?php
/**
 * Created by PhpStorm.
 * User: bruno
 * Date: 30/04/19
 * Time: 11:33
 */

namespace Aluno\Controller;


use Zend\Mvc\Controller\AbstractActionController;
use Zend\View\Model\ViewModel;
use Aluno\Model\AlunoTable;

class AlunoController extends AbstractActionController
{

    private $table;

    public function __construct(AlunoTable $alunoTable)
    {
        $this->table = $alunoTable;
    }

    public function indexAction()
    {
        return new ViewModel(array('alunos'=>$this->table->fetchAll()));
    }

    public function addAction()
    {
    }

    public function editAction()
    {
    }

    public function deleteAction()
    {
    }

}