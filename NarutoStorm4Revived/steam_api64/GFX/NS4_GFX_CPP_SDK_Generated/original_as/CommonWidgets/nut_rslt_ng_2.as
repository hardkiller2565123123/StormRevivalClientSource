package script.icon_result2_brt
{
   import SeIdList.SeId;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol11")]
   public class nut_rslt_ng extends MovieClip
   {
      
      public function nut_rslt_ng()
      {
         super();
         addFrameScript(20,this.frame21,67,this.frame68);
      }
      
      internal function frame21() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MENU_MODE_SEL);
      }
      
      internal function frame68() : *
      {
         gotoAndPlay("loop");
      }
   }
}

