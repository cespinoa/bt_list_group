<?php

declare(strict_types=1);

namespace Drupal\bt_list_group\Plugin\views\style;

use Drupal\Core\Form\FormStateInterface;
use Drupal\views\Plugin\views\style\StylePluginBase;

use Drupal\bootstrap_toolbox\UtilityServiceInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * List Group style plugin.
 *
 * @ViewsStyle(
 *   id = "bt_list_group_list",
 *   title = @Translation("List Group"),
 *   help = @Translation("@todo Add help text here."),
 *   theme = "views_style_bt_list_group_list",
 *   display_types = {"normal"},
 * )
 */
final class BTListGroupList extends StylePluginBase {

  /**
   * {@inheritdoc}
   */
  protected $usesRowPlugin = TRUE;

  /**
   * {@inheritdoc}
   */
  protected $usesRowClass = TRUE;

   /**
   * The utility service.
   *
   * @var \Drupal\bootstrap_toolbox\UtilityServiceInterface
   */
  protected $utilityService;

  /**
   * Constructs a new BTListGroupList object.
   *
   * @param array $configuration
   *   The plugin configuration.
   * @param string $plugin_id
   *   The plugin ID.
   * @param mixed $plugin_definition
   *   The plugin definition.
   * @param \Drupal\bootstrap_toolbox\UtilityServiceInterface $utilityService
   *   The utility service.
   */
  public function __construct(array $configuration, $plugin_id, $plugin_definition, UtilityServiceInterface $utilityService) {
    parent::__construct($configuration, $plugin_id, $plugin_definition);
    $this->utilityService = $utilityService;
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition) {
    return new static(
      $configuration,
      $plugin_id,
      $plugin_definition,
      $container->get('bootstrap_toolbox.utility_service') // Aquí inyectas el servicio
    );
  }

  /**
   * {@inheritdoc}
   */
  protected function defineOptions(): array {

    $options = parent::defineOptions();
    $options['wrapper_class'] = ['default' => 'list-group'];
    $options['view_fields'] = ['default' => ''];
    $options['row_class'] = ['default' => ''];
    $options['display_as_card'] = ['default' => FALSE];
    $options['display_title_as_header'] = ['default' => FALSE];

    $options['card_style'] = ['default' => 'none'];
    $options['header_style'] = ['default' => 'none'];
    $options['body_style'] = ['default' => 'none'];
    
    return $options;
  }

  /**
   * {@inheritdoc}
   */
  public function buildOptionsForm(&$form, FormStateInterface $form_state): void {
    parent::buildOptionsForm($form, $form_state);

    $cardStyleOptions = $this->utilityService->getScopeListFiltered(['cards_formatters']);
    $headerStyleOptions = $this->utilityService->getScopeListFiltered(['header_cards_formatters']);
    $bodyStyleOptions = $this->utilityService->getScopeListFiltered(['body_cards_formatters']);

    $form['display_as_card'] = [
      '#type' => 'checkbox',
      '#title' => $this->t('Display as Bootstrap card'),
      '#default_value' => $this->options['display_as_card'],
    ];

    $form['display_title_as_header'] = [
      '#type' => 'checkbox',
      '#title' => $this->t('Use display title as card header'),
      '#default_value' => $this->options['display_title_as_header'],
    ];

    $form['card_style'] = [
      '#type' => 'select',
      '#title' => t('Card style'),
      '#default_value' => $this->options['card_style'],
      '#options' => $cardStyleOptions,
      '#empty_option' => 'None',
      '#states' => [
        'visible' => [
          ':input[name="style_options[display_as_card]"]' => ['checked' => TRUE],
        ],
      ],
    ];
  
    $form['header_style'] = [
      '#type' => 'select',
      '#title' => t('Header style'),
      '#default_value' => $this->options['header_style'],
      '#options' => $headerStyleOptions,
      '#empty_option' => 'None',
      '#states' => [
        'visible' => [
          ':input[name="style_options[display_as_card]"]' => ['checked' => TRUE],
        ],
      ],
    ];
    
    $form['body_style'] = [
      '#type' => 'select',
      '#title' => t('Body style'),
      '#default_value' => $this->options['body_style'],
      '#options' => $bodyStyleOptions,
      '#empty_option' => 'None',
      '#states' => [
        'visible' => [
          ':input[name="style_options[display_as_card]"]' => ['checked' => TRUE],
        ],
      ],
    ];
    
    
  }

  public function elementPreRenderRow(array $data) {


    /*
     *
     * Falta añadir cabecera y formatear como card
     *
     * */

  
    foreach ($this->view->field as $id => $field) {
      $url = $data['#row']->_entity->toLink()->getUrl()->toString();
      $active = $this->checkUrl($url);
   
      $field->options['settings']['link_to_entity'] = FALSE;
      $field->options['alter']['make_link'] = TRUE;
      $field->options['alter']['path'] = $url;
      $field->options['alter']['link_class'] = 'list-group-item list-group-item-action '. $active;
      $field->options['alter']['alter_text'] = TRUE;
        $data[$id] = [
            '#markup' => $field->theme($data['#row']),
        ];
    }
    
    return $data;
  }



  public function checkUrl($url){
    $active = '';
    $currentEntityUrl = NULL;
    $routeMatch = \Drupal::routeMatch();
    $routeMatch = \Drupal::service('current_route_match');
    $route = $routeMatch->getRouteName();

    $routeElements = explode('.',$route);
    if($routeElements[0] == 'entity' && $routeElements[2] == 'canonical'){
      $currentEntity = $routeMatch->getParameter($routeElements[1]);
      $currentEntityToLink = $currentEntity->toLink();
      $currentEntityUrl = $currentEntityToLink->getUrl()->toString();
    }

    if( $url == $currentEntityUrl){
      $active = 'active';
    }

    return $active;
  }




  
}
