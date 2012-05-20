$(document).ready(function() {
  var map;
  function initialize() {
    $.getJSON(Drupal.settings.base_url + '/issue/gmap/ajax/'+ nid, function(data) {
      var beaches = [];
      var latitude, longitud;
      $.each(data, function(key, val) {
        for (i in val) {
          //  beaches.push(val[i].latitude, val[i].longitude);
          beaches[i]= [val[i].latitude, val[i].longitude, val[i].color];
        }
        latitude = val[0].latitude;
        longitude = val[0].longitude;
      });

      var myLatlng = new google.maps.LatLng(latitude, longitude);
      var myOptions = {
        zoom: 1,
        center: myLatlng,
		mapTypeControl: false,
		mapTypeControlOptions: {style: google.maps.MapTypeControlStyle.DROPDOWN_MENU},
		navigationControl: true,
		navigationControlOptions: {style: google.maps.NavigationControlStyle.SMALL},
		mapTypeId: google.maps.MapTypeId.ROADMAP
      }
      map = new google.maps.Map(document.getElementById("map_div"), myOptions);
      var nid = $('#curr_nid').val();
      
      setCircles(map, beaches);
      setMarkers(map, beaches);
    });
  }
  
  function setCircles(map, locations) {
    for (var i = 0; i < locations.length; i++) {
      var beach = locations[i];
      var myLatLng = new google.maps.LatLng(beach[0], beach[1]);
      var marker = new google.maps.Circle({
        strokeColor: beach[2],
        strokeOpacity: 0.8,
        strokeWeight: 2,
        fillColor: beach[2],
        fillOpacity: 0.35,
        map: map,
        center: myLatLng,
        radius: 10000
      });
    }
  }
  function setMarkers(map, locations) {

    for (var i = 0; i < locations.length; i++) {
    
      var beach = locations[i];
      var myLatLng = new google.maps.LatLng(beach[0], beach[1]);
      var marker = new google.maps.Marker({
        position: myLatLng, 
        map: map,
        
        // icon: 'http://google-maps-icons.googlecode.com/files/factory.png'
        icon: Drupal.settings.base_url+ '/'+Drupal.settings.google_map_icons+'/'+beach[2].replace('#','')+ '.png'
      })
    }
    
  }
  initialize();
});