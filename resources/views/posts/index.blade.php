@extends('layouts/app')

@section('content')

    <h1>POST</h1>
    <br>
    <br>
    @if(count($posts) > 0)
        @foreach($posts as $post)
            <div class="card p-3 mt-3 mb-3">
                <div class="row">
                    <div class="col-md-4 col-sm-4">
                        <img style="width:100%" src="/storage/cover_image/{{$post->cover_image}}">
                    </div>
                    <div class="col-md-8 col-sm-8">
                        <h3><a href="/posts/{{$post->id}}">{{$post->title}}</a></h3>
                        <small>written on {{$post->created_at}} by {{$post->user->name}}</small>
                    </div>
                </div>
            </div>
        @endforeach
        {{$posts->links()}}
    @else
        <p>no post found</p>
    @endif

@endsection