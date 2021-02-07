<?php
/**
 * Created by PhpStorm.
 * User: bruno
 * Date: 30/04/19
 * Time: 11:37
 */

namespace Aluno\Model;


class Aluno
{
    public $nome;
    public $cpf;
    public $email;
    public $id;

    public function exchangeArray(array $data)
    {
        $this->cpf = !empty($data['cpf']) ? $data['cpf']:null;
        $this->nome = !empty($data['nome']) ? $data['nome']:null;
        $this->email = !empty($data['email']) ? $data['email']:null;
        $this->id = !empty($data['id']) ? $data['id']:null;
    }

}