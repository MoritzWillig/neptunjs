/**
 * Class for logging test results
**/
function Tester() {
  var tests=[];
  var success=[];
  var err=[];
  var aborted=[];
  var testnames=[];

  var mods={
    "normal":"0m", //or 49m ?
    "black" :"30m",
    "red"   :"31m",
    "green" :"32m",
    "blue"  :"34m",
    "yellow":"33m"
  }
  var changeColor=function(c) {
    ob.write("\u001B["+mods[c]);
  }
  this.success=function(silent) {
    if (silent!=true) {
      changeColor("green");
      ob.write("ok");
      changeColor("normal");
    }
    success[success.length-1]++;
  };
  this.failed=function(silent) {
    if (silent!=true) {
      changeColor("red");
      ob.write("failed");
      changeColor("normal");
    }
    err[err.length-1]++;
  };
  this.abort=function(silent) {
    if (silent!=true) {
      changeColor("yellow");
      ob.write("aborted. Skipping following ...");
      changeColor("normal");
    }
    aborted[aborted.length-1]++;
  };
  this.isAborted=function() { return (aborted[aborted.length-1]!=0); }
  this.getCurrentResults=function() {
    return {
      "success":success[success.length-1],
      "failed" :err[err.length-1],
      "aborted" :aborted[aborted.length-1],
      "isAborted":this.isAborted()
    }
  }

  this.startUnit=function(testname) {
    testnames.push(testname);
    ob.writeln("Testing "+testnames[testnames.length-1]+": ");
    tests.push(0);
    success.push(0);
    err.push(0);
    aborted.push(0);
  }

  this.abortUnit=function(reason) {
    if (!reason) { reason="No reason given"; }
    ob.write("Aborting Unit: "+reason+": ");
    this.abort();
    ob.writeln("");
    this.endUnit();
  }

  this.endUnit=function() {
    var c=this.getCurrentResults();

    ob.write("Ended test "+testnames[testnames.length-1]+" [");
    changeColor("green");
    ob.write(c.success);
    changeColor("normal"); ob.write('|');
    changeColor("red");
    ob.write(c.failed);
    if (c.isAborted) {
      changeColor("normal"); ob.write('|');
      changeColor("yellow");
      ob.write("skipped("+c.aborted+")");
    };
    changeColor("normal");
    ob.writeln("]");

    testnames.pop();
    tests.pop();
    success.pop();
    err.pop();
    aborted.pop();

    if (testnames.length!=0) {
      if (c.isAborted) {
        this.abort(true);
      } else {
        (c.failed==0)?this.success(true):this.failed(true);
      }
    }
  };

  this.test=function(name,testfunc) {
    ob.write("Testing \""+name+"\": ");

    if (!this.isAborted()) {
      try {
        var r=testfunc();
        if (r=="skip") {
          this.abort();
        } else {
          (r==true)?this.success():this.failed();
        }
      } catch(e) {
        this.failed();
      }
    } else { this.abort(); }
    ob.writeln();
  }
}


function test_permissions() {
  tester.startUnit("Permission class");
  
  tester.test("Permission creation",function() {
    try {
      var pm=new Permission();
      return false;
    } catch(e) {
      return true;
    }
  });
  
  //tester.test("Permission security");
  if ((typeof(permissions           )!='undefined') &&
      (typeof(permissions["sql"]   )!='undefined') &&
      (typeof(permissions["sql"][0])!='undefined')) {
      var p=permissions["sql"][0];
      
      var pm;
      tester.test("Permission instancing",function() {
        try {
          pm=new Permission(permissions["sql"][0]);
          return true;
        } catch(e) {
          return false;
        }
      });
    
    tester.test("Trace lock",function() {
      if (pm.traceLocked==true) {
        ob.writeln("Couldn't test. Trace is already locked");
        return "skip";
      } else {
        pm.lockTrace();
        return pm.traceLocked;
      }
    });
    
    } else {
      ob.writeln("Couldn't test permissions. No permissions were given.");
    return "skip";
    }
    
    tester.endUnit();
}

/**
 * Tests the functionality of the file object
**/
function test_file() {
  tester.startUnit("File Class");
  
  var fl=new File();
  
  tester.test("Allowed access", function() {
    try {
      return fl.load("./samples/testfiles/testfile1");
    } catch(e) {
      ob.writeln(e);
      return false;
    }
  });
  
  tester.test("Denied access", function() {
    try {
      return !fl.load("./samples/testfiles/THIS_FILE-DOES_NOT-EXIST");
    } catch(e) {
      return true;
    }
  });
  
  tester.test("Absolute path", function() {
    var s="./samples/testfiles/testfile1"; fl.load(s);
    ob.writeln("loaded as "+s+" resolved as "+fl.getPath(true));
    return true;
  });
  
  tester.endUnit();
}


function test_sql() {
  //SQL
  tester.startUnit("SQL class");

  //Testing connection
  var msql;
  tester.test("Allowed connection", function() {
    try {
      msql=new SQL();
      msql.connect("127.0.0.1","root","54tzck23");
      if (!msql.isConnected()) { ob.writeln("Is not connected"); return false; }
      return true;
    } catch(e) {
      ob.writeln("couldn't connect");
      ob.writeln("reason: "+e);
      return "skip";
    }
  });

  //Testing feedback on invalid connection attempt
  tester.test("Broken connection", function() {
    try {
      var mfsql=new SQL();
      mfsql.connect("localhost","root","54tzck23falsch");
      return false;
    } catch(e) {
      ob.writeln("connection failed: reason: "+e);
      return true;
    }
  });

  //testing commands on successfull connection
  tester.test("testing commands", function() {
    try {
      msql.execute("USE testdb");
      msql.setCommand("SELECT * FROM testtb");
      var x=msql.query();
      ob.writeln("Found "+x.length+" lines.");
      
      ob.writeln("Displaying line 3");
      for (var i=2; i<3; i++) {
        var y=x[i]; var s="";
        for (var c=0; c<y.length; c++) {
          s+=y[c]+" ";
        }
        ob.writeln("Line "+i+": "+s);
      }
      
      return true;
    } catch(e) {
      ob.writeln("Command failed. Reason: "+e);
      return false;
    }
  });

  tester.endUnit();
}

function test_protection() {
  tester.startUnit("Native Protection");
  
  try {
    var fl =new File();
    var sql=new SQL();
  } catch(e) {
    tester.abortUnit("Can not create native classes");
    return;
  }
  
  tester.test("Call native function on Object", function() {
    try {
      fl.load.apply({},["./samples/testfiles/testfile1"]);
      return false;
    } catch(e) {
      return true;
    }
  });
  
  tester.test("Call native function on extern Object", function() {
    try {
      fl.load.apply(sql,["./samples/testfiles/testfile1"]);
      return false;
    } catch(e) {
      return true;
    }
  });
  
  tester.endUnit();
}

function test_basic() {
  tester.startUnit("Basic functions");

  tester.test("Include extern script", function() {
    try {
      include("./samples/js/paramsInclude.js");
      include("./samples/js/paramsIncludeTagMode.js",true);
      return true;
    } catch(e) {
      return false;
    }
  });
  
  tester.endUnit();
}

(function main() {
//Inp.x+Inp.y+z;

tester=new Tester();

tester.startUnit("testing addins");
ob.writeln("-------");
test_basic();
ob.writeln("-------");
test_permissions();
ob.writeln("-------");
test_file();
ob.writeln("-------");
test_sql();
ob.writeln("-------");
test_protection();
ob.writeln("-------");
tester.endUnit();

})();
