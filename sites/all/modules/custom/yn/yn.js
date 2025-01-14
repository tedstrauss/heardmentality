/**
 * Workaround for YN votes
 *
 * Define your own "yn_success(element, data)" function when you need to run custom actions
 */
$('.yn-a, .yn-d').live('click', function (e) {
  e.preventDefault();
  var el = $(this);
  var url = Drupal.settings.language_prefix+'/yn/' + el.attr('name');
  $.ajax({
    type:"POST",
    dataType:'json',
    url:url,
    success:function (response) {
      if (!response.status) {
        $.hrd.noty({
          text:response.message,
          type:'error'
        });
        return false;
      }
      $.hrd.noty({
        text:response.message,
        type:'success'
      });
      $('body').trigger('yn', [el, response.data]);
    }
  });
});
