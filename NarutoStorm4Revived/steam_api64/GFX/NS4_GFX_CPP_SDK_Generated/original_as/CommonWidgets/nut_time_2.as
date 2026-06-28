package script.hist_cmn
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public class nut_time extends MovieClip
   {
      
      public var txt_msg:smb_font;
      
      public function nut_time()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      public function SetText(param1:String) : *
      {
         var _loc2_:smb_font = smb_font(this["txt_time"]);
         if(_loc2_)
         {
            _loc2_.SetText(param1);
         }
      }
      
      public function GetPlayTime(param1:int) : String
      {
         var _loc2_:int = int(HistParam.CCD_PLAYTIME_TBL[param1]);
         return " " + _loc2_.toString() + " ";
      }
      
      public function SetVisible(param1:Boolean) : *
      {
         this.visible = param1;
      }
      
      internal function frame1() : *
      {
         this.txt_msg.SetText("Version 2016.**.**");
         this.txt_msg.SetTextSize(20);
         this.txt_msg.SetTextPivot(smb_font.CCD_PIVOT_LC);
      }
   }
}

