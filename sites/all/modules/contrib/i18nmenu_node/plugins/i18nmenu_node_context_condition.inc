<?php
// $Id: i18nmenu_node_context_condition.inc,v 1.1 2010/09/18 09:31:30 plach Exp $

/**
 * Expose translated node menu items as a context condition.
 */
class i18nmenu_node_context_condition extends context_condition_menu {
  
  /**
   * Override of execute().
   */
  function execute() {
    // Execute the 'plain' menu condition. This will work for the source nodes.
    parent::execute();

    $trail = menu_get_active_trail();
    foreach ($trail as $item) {
      // If we do not have a matching context we try with the node translations:
      // $item['link_path'] holds the source node path, which can be checked
      // against the condition map successfully. If it is equal to $item['href']
      // we skip the item as it has been already checked before.
      $value = $item['link_path'];
      if (empty($this->values[$value]) && $item['href'] != $value && i18nmenu_node_enabled($item)) {
        foreach ($this->get_contexts($value) as $context) {
          $this->condition_met($context, $value);
        }
      }
    }
  }
}
