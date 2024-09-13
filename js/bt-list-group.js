/**
 * @file
 * Bootstrap Toolbox List_Group behaviors.
 */
(function (Drupal) {

  'use strict';

  Drupal.behaviors.btListGroupBtListGroup = {
    attach (context, settings) {

      // Selecciona todos los elementos con la clase 'bt-list-group-panel'
      const panels = document.querySelectorAll('.bt-list-group-panel');

      panels.forEach(function(panel) {
        // Selecciona el hijo con la clase 'tab-content'
        const tabContent = panel.querySelector('.tab-content');
        // Selecciona el hijo con la clase 'panel-list'
        const panelList = panel.querySelector('.panel-list');

        if (tabContent && panelList) {
          const tabContentHeight = tabContent.offsetHeight;
          const panelListHeight = panelList.offsetHeight;

          // Si panelList es más alto que tabContent, ajusta su altura
          if (panelListHeight > tabContentHeight) {
            panelList.style.height = tabContentHeight + 'px';
            panelList.style.overflowY = 'auto';
          }
        }
      });

    }
  };

} (Drupal));
