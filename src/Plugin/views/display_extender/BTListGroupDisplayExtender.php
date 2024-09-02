<?php

namespace Drupal\bt_list_group\Plugin\views\display_extender;

use Drupal\Core\Form\FormStateInterface;
use Drupal\views\Plugin\views\display_extender\DisplayExtenderPluginBase;

/**
 * Bootstrap Toolbox List Group display extender plugin.
 *
 * @ingroup views_display_extender_plugins
 *
 * @ViewsDisplayExtender(
 *   id = "bt_list_group",
 *   title = @Translation("Bootstrap Toolbox List Group in Views Display Extender"),
 *   help = @Translation("Bootstrap Toolbox List Group In Views settings for this view."),
 *   no_ui = FALSE
 * )
 */
class BTListGroupDisplayExtender extends DisplayExtenderPluginBase {

  /**
   * Provide a form to edit options for this plugin.
   */
  public function buildOptionsForm(&$form, FormStateInterface $formstate) {
    if($this->displayHandler->options['style']['type']=='default'){
      if ($formstate->get('section') == 'style_options') {
        $form['active'] = [
          '#type' => 'checkbox',
          '#title' => $this->t('Display as Bootstrap List Group Nuevo'),
          '#default_value' => $this->options['active'] ?? '',
        ];
      }
    }
  }

  /**
   * Validate the options form.
   */
  public function validateOptionsForm(&$form, FormStateInterface $formstate) {

  }

  /**
   * Handle any special handling on the validate form.
   */
  public function submitOptionsForm(&$form, FormStateInterface $formstate) {
    if ($formstate->get('section') == 'style_options') {
      $this->options['active'] = $formstate->cleanValues()->getValue('active');
    }
  }

  /**
   * Set up any variables on the view prior to execution.
   */
  public function preExecute() {
    $this->view->style_plugin->options['row_class'] = 'list-group-item list-group-item-action';
  }
  

  /**
   * Inject anything into the query that the display_extender handler needs.
   */
  public function query() {

  }

  /**
   * Provide the default summary for options in the views UI.
   *
   * This output is returned as an array.
   */
  public function optionsSummary(&$categories, &$options) {
    
  }

  /**
   * Lists defaultable sections and items contained in each section.
   */
  public function defaultableSections(&$sections, $section = NULL) {

  }


  /**
 * Set up any variables on the view prior to execution.
 */
  //~ public function preRender() {
    
  //~ }

}
