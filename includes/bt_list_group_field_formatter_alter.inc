<?php
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Field\FormatterInterface;
use Drupal\Core\Field\FieldDefinitionInterface;

/**
 * @file
 * Include files for functions and hooks related to field formatter
 */


/**
 * Implements hook_field_formatter_third_party_settings_form().
 */
function bt_list_group_field_formatter_third_party_settings_form(FormatterInterface $plugin, FieldDefinitionInterface $field_definition, $view_mode, $form, FormStateInterface $form_state) {
  $element = [];

  /* @var \Drupal\bt_list_group\Service\InitialSettingsService $initialSettings */
  $initialSettings = \Drupal::service('bt_list_group.initial');

  if (in_array($plugin->getPluginId(), $initialSettings->getFormatters())) {

    $settings = $plugin->getThirdPartySetting('bt_list_group','settings');

    $utilityService = \Drupal::service('bootstrap_toolbox.utility_service');
    $cardStyleOptions = $utilityService->getScopeListFiltered(['cards_formatters']);
    $headerStyleOptions = $utilityService->getScopeListFiltered(['header_cards_formatters']);
    $bodyStyleOptions = $utilityService->getScopeListFiltered(['body_cards_formatters']);


    $element['settings'] = [
      '#type' => 'details',
      '#title' => 'Bootstrap Toolbox List Group',
    ];
    
    $element['settings']['list_group'] = [
      '#type' => 'checkbox',
      '#title' => t('Display as a bootstrap list group'),
      '#default_value' => $settings['list_group'],
    ];
    
    $element['settings']['display_as_a_card'] = [
      '#type' => 'checkbox',
      '#title' => t('Display as a bootstrap card'),
      '#default_value' => $settings['display_as_a_card'],
      '#states' => [
        'visible' => [
          ':input[name="fields[' . $field_definition->getName() . '][settings_edit_form][third_party_settings][bt_list_group][list_group]"]' => ['checked' => TRUE],
        ],
      ],
    ];
    
    $element['settings']['use_label_as_card_header'] = [
      '#type' => 'checkbox',
      '#title' => t('Display label as card_header'),
      '#default_value' => $settings['use_label_as_card_header'],
      '#states' => [
        'visible' => [
          ':input[name="fields[' . $field_definition->getName() . '][settings_edit_form][third_party_settings][bt_list_group][display_as_a_card]"]' => ['checked' => TRUE],
        ],
      ],
    ];

    $element['settings']['card_style'] = [
    '#type' => 'select',
    '#title' => t('Card style'),
    '#default_value' => $settings['card_style'],
    '#options' => $cardStyleOptions,
    '#empty_option' => 'None',
    '#states' => [
      'visible' => [
        ':input[name="fields[' . $field_definition->getName() . '][settings_edit_form][third_party_settings][bt_list_group][display_as_a_card]"]' => ['checked' => TRUE],
      ],
    ],
  ];
  
  $element['settings']['header_style'] = [
    '#type' => 'select',
    '#title' => t('Header style'),
    '#default_value' => $settings['header_style'],
    '#options' => $headerStyleOptions,
    '#empty_option' => 'None',
    '#states' => [
      'visible' => [
        ':input[name="fields[' . $field_definition->getName() . '][settings_edit_form][third_party_settings][bt_list_group][display_as_a_card]"]' => ['checked' => TRUE],
      ],
    ],
  ];
  
  $element['settings']['body_style'] = [
    '#type' => 'select',
    '#title' => t('Body style'),
    '#default_value' => $settings['body_style'],
    '#options' => $bodyStyleOptions,
    '#empty_option' => 'None',
    '#states' => [
      'visible' => [
        ':input[name="fields[' . $field_definition->getName() . '][settings_edit_form][third_party_settings][bt_list_group][display_as_a_card]"]' => ['checked' => TRUE],
      ],
    ],
  ];
    
  }
    
  return $element;
}


/**
 * Implements hook_field_formatter_settings_summary_alter().
 */
function bt_list_group_field_formatter_settings_summary_alter(&$summary, $context) {
  /* @var \Drupal\bt_list_group\Service\InitialSettingsService $initialSettings */
  $initialSettings = \Drupal::service('bt_list_group.initial');
  
  if(in_array($context['formatter']->getPluginId(), $initialSettings->getFormatters())) {
    $customSummary = [];
    if($context['formatter']->getThirdPartySetting('bt_list_group', 'settings')) {
      $settings = $context['formatter']->getThirdPartySetting('bt_list_group', 'settings');
      if($settings['list_group']){
        $customSummary[] = t('Display as a List Group');
        if($settings['display_as_a_card']){
          $customSummary[] = t(' formatted as a Card');
          if($settings['use_label_as_card_header']){
            $customSummary[] = t(' and using label as header');
          }
          if($settings['card_style'] || $settings['header_style'] || $settings['body_style'] ){
            $customSummary[] = t(' with some custom styles');
          }
        }
      }
    }
    $customSummary = implode(' ',$customSummary);
    $summary[] = $customSummary;
  }
}

/**
 *
 * Process the field with third_party_settings 
 * 
 * Implements hook_preprocess_HOOK() for field templates.
 */
function bt_list_group_preprocess_field(&$variables){
  
  if(array_key_exists('#third_party_settings', $variables['element'])
        && array_key_exists('bt_list_group',$variables['element']['#third_party_settings'])
        && array_key_exists('settings',$variables['element']['#third_party_settings']['bt_list_group'])
        && $variables['element']['#third_party_settings']['bt_list_group']['settings']['list_group']){
          
    if(count($variables['items'])){
      $utilityService = \Drupal::service('bootstrap_toolbox.utility_service');
      if(gettype($variables['attributes'])!='object'){
        $variables['attributes'] =  new \Drupal\Core\Template\Attribute();
      }
      $settings = $variables['element']['#third_party_settings']['bt_list_group']['settings'];
      $settings['card_style'] = $utilityService->getStyleById($settings['card_style']);
      $settings['header_style'] = $utilityService->getStyleById($settings['header_style']);
      $settings['body_style'] = $utilityService->getStyleById($settings['body_style']);
      
      $variables['attributes']->addClass('list-group');
      $variables['attributes']->addClass($settings['body_style']);

      
      
      if($settings['display_as_a_card']){
        $variables['attributes']->addClass('card');
        $variables['attributes']->addClass($settings['card_style']);
        if($settings['use_label_as_card_header']){
          $variables['label_class'] = 'card-header ' . $settings['header_style'];
          $variables['label_display'] = 'above';
          $variables['label_hidden'] = FALSE;
        }
      }
      if($variables['items'][0]['content']['#type']=='link'){
        $utilityService = \Drupal::service('bootstrap_toolbox.utility_service');
        foreach($variables['items'] as $delta=>$item){
          $linkUrl = $item['content']['#url']->toString();
          $active = $utilityService->isCurrentUrl($linkUrl) ? 'active' : '';
          $variables['items'][$delta]['content']['#attributes'] = ['class' => ['list-group-item list-group-item-action', $active]];
        }
      }
    }
    $previousClasses = implode(' ',$variables['attributes']->getClass()->value());
    $variables['attributes']->addClass($previousClasses);
  }
  
}

