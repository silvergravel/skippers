//BLACKLISTED WEBSITES
var facebook = "www.facebook";

//check url when user switches to another tab
chrome.tabs.onActivated.addListener(function(evt){
      chrome.tabs.get(evt.tabId, function(tab){
        //console.log(tab.url);

        if(tab.url.indexOf(facebook) != -1 ){
          console.log("get off social media!");

          $.ajaxSetup({timeout:500});
          $.get("http://192.168.2.95:80", {led:"1"});
          // var xhr = new XMLHttpRequest();
          // xhr.open('GET', "http://192.168.2.95:80/?led=1", true);
          // xhr.send();
          {Connection: close};


        } else {
            console.log("your allowed");

            $.ajaxSetup({timeout:500});
            $.get("http://192.168.2.95:80", {led:"0"});
            // var xhr = new XMLHttpRequest();
            // xhr.open('GET', "http://192.168.2.95:80/?led=0", true);
            // xhr.send();
            {Connection: close};


          }
        });
});

//check url when user visits a new url
chrome.tabs.onUpdated.addListener(function(){
  chrome.tabs.query({'active': true, 'lastFocusedWindow': true}, function (tabs) {
    var url = tabs[0].url;
    //console.log("something is updated: " + url);
    if(url.indexOf(facebook) != -1){
      console.log("get off social media!");

      $.ajaxSetup({timeout:2000});
      $.get("http://192.168.2.95:80", {led:"1"});
      // var xhr = new XMLHttpRequest();
      // xhr.open('GET', "http://192.168.2.95:80/?led=1", true);
      // xhr.send();
      {Connection: close};


    } else {
        console.log("your allowed");

        $.ajaxSetup({timeout:2000});
        $.get("http://192.168.2.95:80", {led:"0"});
        // var xhr = new XMLHttpRequest();
        // xhr.open('GET', "http://192.168.2.95:80/?led=0", true);
        // xhr.send();
        {Connection: close};


      }
});

    });
