<?php
$type="default";
if (isset($class) && trim($class)!="") {
    $type = $class;
}
?>
<div id="<?php print $accordion_wapper_id; ?>" class="panel-group <?php print $type;?>">
<?php print $content; ?>
</div>  
