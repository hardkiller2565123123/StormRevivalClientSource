package script.freebtl_set
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base6;
   import script.xcmn_menu.nut_cursor_m;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol41")]
   public class all_handi00 extends MovieClip
   {
      
      public var mc_base3:nut_base6;
      
      public var mc_cursor_l:nut_cursor_m;
      
      public var mc_cursor_r:nut_cursor_m;
      
      public var mc_handi00:MovieClip;
      
      public var mc_sel1:MovieClip;
      
      public var mc_sel2:MovieClip;
      
      public var text_handi00:smb_font;
      
      public function all_handi00()
      {
         var _loc2_:Point = null;
         super();
         addFrameScript(0,this.frame1);
         var _loc1_:smb_font = this["text_handi00"];
         if(_loc1_ != null)
         {
            if(_loc1_.IsArabic() == true)
            {
               _loc2_ = new Point();
               _loc1_.GetTextPos(_loc2_);
               _loc1_.SetTextPos(-_loc2_.x,_loc2_.y);
            }
         }
      }
      
      internal function frame1() : *
      {
         stop();
         if(this.text_handi00.IsArabic() == true)
         {
            this.text_handi00.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.text_handi00.SetTextPivot(smb_font.CCD_PIVOT_RC);
         }
         else
         {
            this.text_handi00.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.text_handi00.SetTextSize(33);
         this.text_handi00.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.text_handi00.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.text_handi00.SetTextFieldWidth(740);
         this.text_handi00.SetTextFit(true);
      }
   }
}

