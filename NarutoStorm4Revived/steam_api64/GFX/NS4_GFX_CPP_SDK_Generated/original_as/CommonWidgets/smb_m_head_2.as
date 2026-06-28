package script.shop_cos
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_line2;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol5")]
   public class smb_m_head extends MovieClip
   {
      
      public var mc_base:MovieClip;
      
      public var mc_line_01:nut_line2;
      
      public var mc_line_02:nut_line2;
      
      public var txt_m_list:smb_font;
      
      public var txt_m_own:smb_font;
      
      public var txt_m_req:smb_font;
      
      private var m_txtList:smb_font = null;
      
      private var m_txtReq:smb_font = null;
      
      private var m_txtOwn:smb_font = null;
      
      private var m_base:MovieClip = null;
      
      private var m_isChangedLayout:Boolean = false;
      
      public function smb_m_head()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_txtList = this["txt_m_list"];
         this.m_txtReq = this["txt_m_req"];
         this.m_txtOwn = this["txt_m_own"];
         this.m_base = this["mc_base"];
      }
      
      private function CheckArabicLayout() : *
      {
         var _loc1_:Number = NaN;
         var _loc2_:Point = null;
         if(this.m_txtList.IsArabic() == true)
         {
            if(this.m_isChangedLayout == false)
            {
               _loc1_ = this.m_base.x;
               _loc2_ = new Point();
               this.m_txtList.GetTextPos(_loc2_);
               this.m_txtList.SetTextPos(_loc2_.x + (_loc1_ - _loc2_.x) * 2,_loc2_.y);
               this.m_txtReq.GetTextPos(_loc2_);
               this.m_txtReq.SetTextPos(_loc2_.x + (_loc1_ - _loc2_.x) * 2,_loc2_.y);
               this.m_txtOwn.GetTextPos(_loc2_);
               this.m_txtOwn.SetTextPos(_loc2_.x + (_loc1_ - _loc2_.x) * 2,_loc2_.y);
               this.m_base.scaleX *= -1;
            }
            this.m_txtList.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.m_txtList.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtReq.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtOwn.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_isChangedLayout = true;
         }
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_m_list.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_m_list.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_m_list.SetTextSize(33);
         this.txt_m_req.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_m_req.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_m_req.SetTextSize(30);
         this.txt_m_own.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_m_own.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_m_own.SetTextSize(30);
         this.CheckArabicLayout();
      }
   }
}

