<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Post extends Model
{
    //overriding table name
    protected $table = 'posts';
    //overriding table primary key
    public $primaryKey = 'id';
    //overriding table timestamps
    public $timestamps = true;

    public function user(){
        return $this->belongsTo('App\User');
    }
}
