<?php

declare(strict_types=1);

namespace Drupal\bt_list_group\Plugin\views\style;

use Drupal\Core\Form\FormStateInterface;
use Drupal\views\Plugin\views\style\StylePluginBase;

/**
 * List Group with Panels style plugin.
 *
 * @ViewsStyle(
 *   id = "bt_list_group_panels",
 *   title = @Translation("Panel List Group"),
 *   help = @Translation("@todo Add help text here."),
 *   theme = "views_style_bt_list_group_panels",
 *   display_types = {"normal"},
 * )
 */
final class BTListGroupPanel extends StylePluginBase {

  /**
   * {@inheritdoc}
   */
  protected $usesRowPlugin = TRUE;

  /**
   * {@inheritdoc}
   */
  protected $usesRowClass = TRUE;

  /**
   * {@inheritdoc}
   */
  protected function defineOptions(): array {
    $options = parent::defineOptions();
    $options['wrapper_class'] = ['default' => 'item-list'];
    $options['view_fields'] = ['default' => 'list-group-item list-group-item-action'];
    return $options;
  }

  /**
   * {@inheritdoc}
   */
  public function buildOptionsForm(&$form, FormStateInterface $form_state): void {
    parent::buildOptionsForm($form, $form_state);
    
    //~ $this->usesFields();
    
    
    
    $fields = [];
    $fieldDefinitions = $this->view->display_handler->handlers['field'];
    if (!empty($fieldDefinitions)) {
      foreach ($fieldDefinitions as $fieldname => $fieldDefinition) {

        $title = $fieldDefinition->configuration['title'];
        if(is_object($title)){
          $title = $title->__toString();
        }
        $fields[$fieldname] = $title;
        
      }
    }

    $positions = [
      'left' => $this->t('Left'),
      'right' => $this->t('Right'),
      'top' => $this->t('Top'),
      'bottom' => $this->t('Bottom'),
    ];

    $form['item_list'] = [
      '#type' => 'select',
      '#title' => $this->t('Select the list element'),
      '#options' => $fields,
      '#default_value' => $this->options['item_list'],
      '#description' => $this->t('Select a field from the view.'),
    ];
    
    $form['selected_panel'] = [
      '#type' => 'select',
      '#title' => $this->t('Select the panel'),
      '#options' => $fields,
      '#default_value' => $this->options['selected_panel'],
      '#description' => $this->t('Select a field from the view.'),
    ];

    $form['list_position'] = [
      '#type' => 'select',
      '#title' => $this->t('List position'),
      '#options' => $positions,
      '#default_value' => $this->options['list_position'],
      '#description' => $this->t('Select the list position.'),
    ];

    
    
    
    
  }

}
