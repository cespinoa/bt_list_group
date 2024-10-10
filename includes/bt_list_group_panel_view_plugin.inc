<?php

/**
 * Prepares variables for views-style-bt-list-group-panels.html.twig template.
 */
function template_preprocess_views_style_bt_list_group_panels(array &$variables): void {
  
  $view = $variables['view'];
  $options = $view->style_plugin->options;

  $variables['default_row_class'] = $options['default_row_class'];
  foreach ($variables['rows'] as $id => $row) {
    $variables['rows'][$id] = [
      'content' => $row,
      'attributes' => new \Drupal\Core\Template\Attribute(),
    ];
    if ($row_class = $view->style_plugin->getRowClass($id)) {
      $variables['rows'][$id]['attributes']->addClass($row_class);
    }
  }
  if($options['list_position'] == 'left' || $options['list_position'] == 'right'){
    $variables['#attached']['library'][] = 'bt_list_group/bt_list_group';
  }
}



/**
 * Implements hook_preprocess_HOOK() for views style templates.
 */
function bt_list_group_preprocess_views_style_bt_list_group_panels(&$variables) {
  
  $view = $variables['view'];
  $stylePlugin = $view->style_plugin;

    
  // Recupera los settings del estilo.
  $styleOptions = $stylePlugin->options;

  // Recupera los valores de los campos desde los settings.
  $itemListField = $styleOptions['item_list'] ?? '';
  $selectedPanelField = $styleOptions['selected_panel'] ?? '';
  


  // Inicializa el array para almacenar las filas.
  $rows = [];
  $listCols = 'col-2';
  $panelCols = 'col-10';
  
  foreach ($view->result as $row_index => $row) {
    $field = $row->_entity->get($itemListField);
    $itemListType = $field->getFieldDefinition()->getType();
    $itemListValue = NULL;
    
    
    if($itemListType == 'string'){
      
      $itemListValue = $field->value;
      $listCols = 'col-3';
      $panelCols = 'col-9';
      
    } elseif($itemListType == 'entity_reference'){

      if($field->getSettings()['target_type'] == 'media'){

        if (!$field->isEmpty()) {
          $mediaEntity = $field->first()->entity;
          if ($mediaEntity) {
            $displayMode = $view->getDisplay()->getOption('fields')[$itemListField]['settings']['view_mode'] ?? 'full';
            $mediaView = \Drupal::entityTypeManager()->getViewBuilder('media')->view($mediaEntity, $displayMode);
            $itemListValue =  \Drupal::service('renderer')->render($mediaView);
          }
        }
      }
      $listCols = 'col-2';
      $panelCols = 'col-10';
    }
    
    
    // Obtiene el valor formateado del campo selected_panel.
    $selectedPanelValue = $view->style_plugin->getField($row_index, $selectedPanelField);

    // Guarda los valores en el array.
    $rows[] = [
      'item_list' => $itemListValue,
      'selected_panel' => $selectedPanelValue,
    ];
    $variables['#attached']['library'][] = 'bt_list_group/images_list';
    
  }


  

  // Guarda el array en las variables para usarlo en la plantilla.
  $variables['rows'] = $rows;
  $variables['list_position'] = $styleOptions['list_position'];
  
  if($styleOptions['list_position'] == 'top' || $styleOptions['list_position'] == 'bottom'){
    $variables['direction'] = 'horizontal';
    $variables['list_cols'] = 'col-12';
    $variables['panel_cols'] = 'col-12';
  } else {
    $variables['direction'] = '';
    $variables['list_cols'] = $listCols;
    $variables['panel_cols'] = $panelCols;
  }
    

}
