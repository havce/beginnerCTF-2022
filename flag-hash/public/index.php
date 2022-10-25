<?php
echo "<div class='center'>Insert the correct flag to view the correct flag</div>";
?>

<html>
    <title>Flag Comparison</title>
    <link rel="stylesheet" href="index.css">
    <body>
        <div class="center">
            <form action="" method="POST">
                <input type="text" name="flag">
                <input type="submit" name="submit" value="compare">
            </form>
        </div>
    </body>
</html>

<?php

$file = getenv('FLAG');
$real_flag_md5 = md5($file);
echo "<div class='center'>To help you this is the md5 of the real flag: <br></br>" . $real_flag_md5 . "</div>";

if (!isset($_POST['flag']) || empty($_POST['flag'])){
    $flag = md5('errorrrrrr');
}
else{
    $flag = $_POST['flag'];
    $flag_md5 = md5($flag);
    if ($flag_md5 == $real_flag_md5){
        echo '<br></br>You got it right!! Take the flag: '.$file;
    }else{
        echo '<br></br>Try again';
    }
}
?>