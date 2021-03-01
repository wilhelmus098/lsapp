<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;

class PagesController extends Controller
{
    public function index(){
        $title = 'welcome to laravel';
        //return view('pages.index',compact('title'));
        return view('pages.index')->with('title1', $title);
    }
    public function about(){
        $title = 'about laravel';
        //return view('pages.about');
        return view('pages.about')->with('title1', $title);
    }
    public function services(){
        $data = array(
            'title' => 'Services',
            'services' => ['webdes','programming','seo','microcontroller']
        );
        return view('pages.services')->with($data);
    }
}
