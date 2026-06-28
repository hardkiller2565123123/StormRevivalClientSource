package script.freebtl_tonmt
{
   import SeIdList.SeId;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.ExternalInterface;
   import script.icon_trop.smb_trop;
   import script.xcmn_eff2.smb_xef_sun1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public dynamic class nut_trop extends MovieClip
   {
      
      public var mc_trop:smb_trop;
      
      public var mc_eff1:smb_xef_sun1;
      
      public function nut_trop()
      {
         super();
         addFrameScript(44,this.frame45,48,this.frame49,53,this.frame54,56,this.frame57,59,this.frame60,62,this.frame63,66,this.frame67,75,this.frame76,102,this.frame103);
      }
      
      public function fl_RotateContinuously_4(param1:Event) : *
      {
         this.mc_eff1.rotation += 0.5;
      }
      
      internal function frame45() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_PUNCH_SWING);
      }
      
      internal function frame49() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_FOOT_SNOW);
      }
      
      internal function frame54() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_FOOT_SNOW);
      }
      
      internal function frame57() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_FOOT_SNOW);
      }
      
      internal function frame60() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_FOOT_SNOW);
      }
      
      internal function frame63() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_FOOT_SNOW);
      }
      
      internal function frame67() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_FOOT_SNOW);
      }
      
      internal function frame76() : *
      {
         this.stop();
         this.mc_eff1.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_4);
      }
      
      internal function frame103() : *
      {
         this.stop();
      }
   }
}

