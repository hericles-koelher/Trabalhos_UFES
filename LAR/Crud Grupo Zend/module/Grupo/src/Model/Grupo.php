<?php


namespace Grupo\Model;


class Grupo
{
    public $id;
    public $nome;

    public function exchangeArray(array $data)
    {
        $this->id = !empty($data['id']) ? $data['id']:null;
        $this->nome = !empty($data['nome']) ? $data['nome']:null;
    }

}