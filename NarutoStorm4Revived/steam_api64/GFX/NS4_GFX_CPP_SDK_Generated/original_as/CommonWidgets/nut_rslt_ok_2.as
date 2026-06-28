package script.icon_result2_brt
{
   import SeIdList.SeId;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol7")]
   public class nut_rslt_ok extends MovieClip
   {
      
      internal var m_isEnableSe:Boolean = true;
      
      public function nut_rslt_ok()
      {
         super();
         addFrameScript(19,this.frame20,84,this.frame85);
      }
      
      public function DisableSe() : *
      {
         this.m_isEnableSe = false;
      }
      
      internal function frame20() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MENU_MODE_SEL);
      }
      
      internal function frame85() : *
      {
         gotoAndPlay("loop");
      }
   }
}

