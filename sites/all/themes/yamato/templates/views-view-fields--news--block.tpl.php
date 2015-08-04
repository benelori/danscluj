<?php $node = $row->_entity_properties['entity object'];
$view = node_view($node, 'dexp_portfolio');
print render($view); ?>
