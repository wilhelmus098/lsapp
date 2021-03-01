<?php

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

//DYNAMIC ROUTE
// Route::get('/users/{id}/{name}', function ($id,$name) {
//     return 'this is user '.$name.' with an id of '.$id;
// });

//DEFAULT STATIC ROUTE
// Route::get('/about', function () {
//     return view('pages.about');
// });

// you dont want to return view
// you want to return to controller that redirect to view


Route::get('/', 'PagesController@index');
Route::get('/about', 'PagesController@about');
Route::get('/services', 'PagesController@services');

Route::resource('posts', 'PostsController');
Auth::routes();

Route::get('/home', 'HomeController@index')->name('home');
