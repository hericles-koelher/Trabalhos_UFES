<?php
/**
 * Created by PhpStorm.
 * User: bruno
 * Date: 30/04/19
 * Time: 11:42
 */

namespace Aluno\Model;

use RuntimeException;
use Zend\Db\TableGateway\TableGatewayInterface;


class AlunoTable
{

    private $tableGateway;

    //O construtor recebe o objeto que irá intermediar a conexão entre a classe e a table selecionada,
    // lembrando que a table também está em uma database
    public function __construct(TableGatewayInterface $tableGateway)
    {
        $this->tableGateway = $tableGateway;
    }

    //Aparentemente o metodo select de TableGatewayInteface quando recebe somente o parametro null
    // retorna todos os campos da table selecionada
    public function fetchAll(){
        return $this->tableGateway->select();
    }

    public function getAluno(int $id){
        //Duvida no tipo de objeto retornado pelo select
        $rowset = $this->tableGateway->select(['id' => $id]);
        //Quais metodos tem esse objeto retornado???
        $row = $rowset->current();

        if(! $row){
            throw new RuntimeException(sprintf(
                "Could not find row with identifier %d",
                $id
            ));
        }

        return $row;

    }

    public function deleteAluno(int $id){
        $this->tableGateway->delete(array('id'=>$id));
    }

    public function saveAluno(Aluno $aluno){

        $data = array('cpf'=>$aluno->cpf,
                      'nome'=>$aluno->nome,
                      'email'=>$aluno->email);

        //typecast de null para int é igual a 0??
        //somente nesse caso o codigo abaixo faz sentido
        $id = (int)$aluno->id;

        //Essa parte insere um aluno novo
        if($id === 0){
            $this->tableGateway->insert($data);
            return;
        }

        //Se chegar aqui significa que o aluno supostamente existe no banco de dados
        try{
            $this->getAluno($id);
        }catch (RuntimeException $exception){
            throw new RuntimeException(sprintf("Cannot update aluno with identifier %d; does not exist",
                $id));
        }

        $this->tableGateway->update($data,array('id'=>$id));
    }


}