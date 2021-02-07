<?php

namespace Grupo\Model;

use Zend\Validator\Regex;
use Zend\Validator\StringLength;

class NameValidator
{

    private $valName;
    private $valStringLen;

    public function __construct()
    {
        $this->valName = new Regex(array('pattern'=>'/^[\p{Latin}\p{Zs}]+$/'));
        $this->valStringLen = new StringLength(array('max'=>30));
    }

    public function isValid(String $string)
    {
        return $this->valStringLen->isValid($string) && $this->valName->isValid($string);
    }
}