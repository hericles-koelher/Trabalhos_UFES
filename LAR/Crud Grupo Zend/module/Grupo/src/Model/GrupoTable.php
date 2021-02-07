<?php


namespace Grupo\Model;

use RuntimeException;
use Zend\Db\TableGateway\TableGatewayInterface;

class GrupoTable
{

    private $tableGateway;

    public function __construct(TableGatewayInterface $tableGateway)
    {
        $this->tableGateway = $tableGateway;
    }

    public function fetchAll()
    {
        return $this->tableGateway->select();
    }

    public function getGrupo(int $id)
    {
        $row = $this->tableGateway->select(['id'=>$id])->current();

        if(!$row){
            throw new RuntimeException(sprintf('Não foi possivel encontrar a linha com ID %d',$id));
        }

        return $row;
    }

    public function saveGrupo(Grupo $gp)
    {
        $data = ['nome' => $gp->nome];

        $id = (int) $gp->id;

        if($id === 0){
            $this->tableGateway->insert($data);
            return;
        }

        try{
            $this->getGrupo($id);
        }catch (RuntimeException $e){
            throw new RuntimeException(sprintf('Não foi possivel encontrar a linha com ID %d',$id));
        }

        $this->tableGateway->update($data,['id' => $id]);
    }

    function deleteGrupo(int $id)
    {
        $this->tableGateway->delete(['id' => $id]);
    }
}