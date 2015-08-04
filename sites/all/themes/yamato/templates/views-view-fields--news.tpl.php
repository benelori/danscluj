<?php $node = $row->_entity_properties['entity object'];
$view = node_view($node, 'teaser');
print render($view); ?>
