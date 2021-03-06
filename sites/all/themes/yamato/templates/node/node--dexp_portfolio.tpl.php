<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix row"<?php print $attributes; ?>>
  <div class="content"<?php print $content_attributes; ?>>
    <?php
// We hide the comments and links now so that we can render them later.
    hide($content['comments']);
    hide($content['links']);    
    ?>
    <div class="portfolio-image col-md-7">
      <?php print render($content['field_portfolio_images']); ?>
    </div>
    <div class="portfolio-details col-md-5">
      <h3 class="headline"><?php print $node->title;?></h3>
      <span class="brd-headling"></span>
      <div class="clearfix"></div>
      <p><?php print render($content['body']); ?></p>
    </div>
  </div>
</div> 