<?php
include_once('connection.php');

if(isset($_POST['register']))
{
    $name=$_POST['name'];
    $username=$_POST['username'];
    $pass=md5($_POST['password']);

    $sql   ="INSERT INTO `tabl_user`(`id`, `name`, `username`, `password`) VALUES (NULL,'$name','$username','$pass')";
    $result=mysqli_query($conn,$sql);
    if($result){ 
    header('location:index.php');
    echo"<script>alert('New User Register Success');</script>";   
    }else{
        die(mysqli_error($conn)) ;
    }
   
}
