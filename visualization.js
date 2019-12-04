var val;
var colorInc = 100 / 3;
var max;
var min;
var weight;


$(function() {
    window.setInterval(function() {

        var deviceID = "400032001051373331333230";
        var accessToken = "f244832f72ff1f44f5e4396fb8bde113ea6b4d6e";
        var varName = "Value";
        var minName = "empty";

        var maxName = "full";

        requestURL = "https://api.spark.io/v1/devices/" + deviceID + "/" + minName + "/?access_token=" + accessToken;
        $.getJSON(requestURL, function(json) {
            min = json.result;

        });
        requestURL = "https://api.spark.io/v1/devices/" + deviceID + "/" + maxName + "/?access_token=" + accessToken;
        $.getJSON(requestURL, function(json) {
            max = json.result;

        });


        requestURL = "https://api.spark.io/v1/devices/" + deviceID + "/" + varName + "/?access_token=" + accessToken;
        $.getJSON(requestURL, function(json) {

            if (weight <= min && weight === "undefined") {
                $(".progress .percent").text("There is no glass on the table%");
            }
            weight = json.result;
            val = 100 * ((weight - min) / (max - min));
            val = Math.floor(val);




            if (val != "" &&
                !isNaN(val) &&
                val <= 100 &&
                val >= 0) {
                console.log(val);

                var valOrig = val;
                val = 100 - val;

                // if (valOrig == 0) {
                //     // $("#percent-box").val(0);
                //     $(".progress .percent").text(0 + "%");
                // } else $(".progress .percent").text(valOrig + "%");

                $(".progress").parent().removeClass();
                $(".progress .water").css("top", val + "%");

                if (valOrig < colorInc * 1)
                    $(".progress").parent().addClass("red");
                else if (valOrig < colorInc * 2)
                    $(".progress").parent().addClass("orange");
                else
                    $(".progress").parent().addClass("green");
            } else {
                $(".progress").parent().removeClass();
                $(".progress").parent().addClass("green");
                $(".progress .water").css("top", 100 - 100 + "%");
                // $(".progress .percent").text(0 + "%");
                $("#percent-box").val("");
            }



        });
    }, 1000);


    // $("#percent-box").click(function() {
    //     $(this).select();
    // });

    // $("#percent-box").keyup(function() {
    //     var val = $(this).val();


    // });
});