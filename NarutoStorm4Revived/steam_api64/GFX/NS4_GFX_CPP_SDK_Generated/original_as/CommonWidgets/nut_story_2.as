package script.hist_cmn_brt
{
   import SeIdList.SeId;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol5")]
   public class nut_story extends MovieClip
   {
      
      public var txt_story:smb_font;
      
      public function nut_story()
      {
         super();
         addFrameScript(0,this.frame1,9,this.frame10,16,this.frame17);
         this.visible = false;
      }
      
      public function Open(param1:String) : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_BOOK);
         this.visible = true;
         this.txt_story.SetText(ExternalInterface.call("MessageConvert",param1));
         this.gotoAndPlay("in");
      }
      
      public function Close() : *
      {
         ExternalInterface.call("RequestPlaySE_Cancel");
         this.gotoAndPlay("out");
      }
      
      internal function frame1() : *
      {
         this.txt_story.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_story.SetTextSize(28);
         this.txt_story.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_story.SetTextFieldWidth(1720);
         this.txt_story.SetTextWordWrap(true);
      }
      
      internal function frame10() : *
      {
         this.stop();
      }
      
      internal function frame17() : *
      {
         this.stop();
         this.visible = false;
      }
   }
}

