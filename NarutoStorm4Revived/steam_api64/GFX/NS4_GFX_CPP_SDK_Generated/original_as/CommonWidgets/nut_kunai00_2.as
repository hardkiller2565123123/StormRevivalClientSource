package script.freebtl_cutin
{
   import SeIdList.SeId;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol32")]
   public dynamic class nut_kunai00 extends MovieClip
   {
      
      public function nut_kunai00()
      {
         super();
         addFrameScript(0,this.frame1,14,this.frame15,21,this.frame22,29,this.frame30,37,this.frame38,45,this.frame46,53,this.frame54,57,this.frame58,64,this.frame65,72,this.frame73,80,this.frame81,88,this.frame89,96,this.frame97,100,this.frame101,119,this.frame120);
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame15() : *
      {
         this.stop();
      }
      
      internal function frame22() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MONEY2);
      }
      
      internal function frame30() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MONEY2);
      }
      
      internal function frame38() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MONEY2);
      }
      
      internal function frame46() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MONEY2);
      }
      
      internal function frame54() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MONEY2);
      }
      
      internal function frame58() : *
      {
         this.stop();
      }
      
      internal function frame65() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MONEY2);
      }
      
      internal function frame73() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MONEY2);
      }
      
      internal function frame81() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MONEY2);
      }
      
      internal function frame89() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MONEY2);
      }
      
      internal function frame97() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MONEY2);
      }
      
      internal function frame101() : *
      {
         stop();
      }
      
      internal function frame120() : *
      {
         stop();
      }
   }
}

