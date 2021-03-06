<?php
/**
 * @file
 * theme.inc
 */

/**
 * Implements hook_theme().
 *
 * Return various tpl files.
 */
function frontend_theme($existing, $type, $theme, $path) {
  $theme_declaration = array();
  $theme_declaration['panels_default_style_render_region'] = array(
    'arguments' =>  array('display' => NULL, 'owner_id' => NULL, 'panes' => NULL, 'settings' => NULL, 'region_id' => NULL, 'style' => NULL),
    'template' => 'templates/panelregions/panels-default-style-render-region'
  );
  return $theme_declaration;
}

/**
 * Implements hook_html_head_alter().
 *
 * Remove favicon.
 */
function frontend_html_head_alter(&$head_elements) {
  foreach ($head_elements as $key => $value) {
    if (!empty($value['#attributes']['rel']) && ($value['#attributes']['rel'] == 'shortcut icon')) {
      unset($head_elements[$key]);
    }
  }
}

/**
 * Implements theme_preprocess_search_result().
 */
function frontend_preprocess_search_result(&$vars) {
  $result = $vars['result'];
  $node = $result['node'];
  $vars['rendered_node'] = node_view($node, 'search_result');
}

/**
 * Implementation of hook_preprocess_html().
 */
function frontend_preprocess_html() {
  global $user;
  if ($user->uid > 0) {
    drupal_add_css(drupal_get_path('theme', 'frontend') . '/assets/stylesheets/application.css', array('group' => CSS_THEME - 1, 'every_page' => TRUE));
    $settings = array(
      'CToolsModal' => array(
        'loadingText' => t('Loading...'),
        'closeText' => t('Close Window'),
        'closeImage' => theme('image', array(
          'path' => ctools_image_path('icon-close-window.png'),
          'title' => t('Close window'),
          'alt' => t('Close window'),
        )),
        'throbber' => theme('image', array(
            'path' => ctools_image_path('throbber.gif'),
            'title' => t('Loading...'),
            'alt' => t('Loading'),
          )),
        'modalSize' => array(
          'type' => 'scale',
          'width' => .8,
          'height' => .8,
          'addWidth' => 0,
          'addHeight' => 0,
          'contentRight' => 45,
          'contentBottom' => 85
        ),
      ),
    );
    drupal_add_js($settings, 'setting');
  }
}

/**
 * Implementation of hook_preprocess_page().
 */
function frontend_preprocess_page(&$vars) {
  $header = drupal_get_http_header('status');
  if ($header == '404 Not Found') {
    $vars['theme_hook_suggestions'][] = 'page__404';
  }
  elseif ($header == '403 Forbidden') {
    $vars['theme_hook_suggestions'][] = 'page__403';
  }
}
