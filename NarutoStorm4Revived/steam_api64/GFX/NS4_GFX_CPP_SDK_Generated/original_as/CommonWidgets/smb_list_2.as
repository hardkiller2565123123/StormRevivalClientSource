package script.map_sm
{
   import flash.display.Bitmap;
   import flash.display.BitmapData;
   import flash.display.MovieClip;
   import flash.utils.getDefinitionByName;
   import script.xcmn_font.smb_font;
   import script.xcp_frame1.smb_xcp_frame1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol44")]
   public class smb_list extends MovieClip
   {
      
      public var all_lst:smb_xcp_frame1;
      
      private const CCD_PLATE_WIDTH:Number = 700;
      
      private const CCD_ICON_X_MARGIN:Number = 30;
      
      private const CCD_ICON_Y_MARGIN:Number = 20;
      
      private const CCD_LIST_LEADER:Number = 2;
      
      private const CCD_TEXT_SIZE:Number = 28;
      
      private const CCD_TEXT_ICON_MARGIN:Number = 15;
      
      private const CCD_ICON_DEFAULT_SIZE:Number = 40;
      
      private const CCD_LIMIT_WINDOW_Y:Number = 400;
      
      private const CCD_TEXT_VIEW_WIDTH:Number = 330;
      
      private const CCD_RIGHT_SAFEFRAME:Number = 150;
      
      private var m_plate:MovieClip = null;
      
      private var m_textCtn:Array = new Array();
      
      private var m_iconCtn:Array = new Array();
      
      public function smb_list()
      {
         super();
         this.m_plate = this["all_lst"];
         this.m_plate.width = this.CCD_PLATE_WIDTH;
      }
      
      public function CreateIconListMenu(param1:Array) : *
      {
         var _loc8_:smb_font = null;
         var _loc9_:uint = 0;
         var _loc10_:String = null;
         var _loc11_:Class = null;
         var _loc12_:BitmapData = null;
         var _loc13_:Bitmap = null;
         var _loc14_:Number = NaN;
         var _loc2_:Number = 0;
         var _loc3_:int = 0;
         while(_loc3_ < param1.length)
         {
            _loc8_ = new smb_font();
            _loc8_.SetTextSize(this.CCD_TEXT_SIZE);
            _loc9_ = _loc8_.IsArabic() == false ? smb_font.CCD_PIVOT_LC : smb_font.CCD_PIVOT_RC;
            _loc10_ = _loc8_.IsArabic() == false ? smb_font.CCD_ALIGN_LEFT : smb_font.CCD_ALIGN_RIGHT;
            _loc8_.SetTextPivot(_loc9_);
            _loc8_.SetTextAlign(_loc10_);
            _loc8_.SetText(param1[_loc3_].m_txt);
            _loc8_.SetTextFieldWidth(this.CCD_TEXT_VIEW_WIDTH);
            _loc8_.SetTextScroll(true);
            addChild(_loc8_);
            this.m_textCtn.push(_loc8_);
            _loc11_ = getDefinitionByName("FacilityIcon_" + param1[_loc3_].m_iconType.toString()) as Class;
            _loc12_ = new _loc11_(0,0);
            _loc13_ = new Bitmap(_loc12_);
            _loc13_.smoothing = true;
            _loc13_.height = _loc13_.width = this.CCD_ICON_DEFAULT_SIZE;
            addChild(_loc13_);
            this.m_iconCtn.push(_loc13_);
            _loc2_ += _loc8_.GetSymbolHeight();
            _loc3_++;
         }
         _loc2_ += this.CCD_ICON_Y_MARGIN * 2 + this.CCD_LIST_LEADER * (this.m_textCtn.length - 1);
         this.m_plate.height = _loc2_;
         if(this.y + this.m_plate.height / 2 > this.CCD_LIMIT_WINDOW_Y)
         {
            this.m_plate.y = this.CCD_LIMIT_WINDOW_Y - (this.y + this.m_plate.height / 2);
         }
         var _loc4_:Number = this.m_plate.y - _loc2_ / 2 + this.CCD_ICON_Y_MARGIN;
         var _loc5_:Number = this.m_plate.x - this.m_plate.width / 2 + this.CCD_ICON_X_MARGIN;
         var _loc6_:Number = this.CCD_RIGHT_SAFEFRAME;
         var _loc7_:Number = 0;
         _loc3_ = 0;
         while(_loc3_ < param1.length)
         {
            _loc7_ += this.m_textCtn[_loc3_].GetSymbolHeight() / 2;
            _loc14_ = this.m_textCtn[_loc3_].GetRubyTextHeight / 2;
            this.m_iconCtn[_loc3_].y = _loc4_ + this.CCD_LIST_LEADER * _loc3_ + _loc7_ + _loc14_ - this.m_iconCtn[_loc3_].height / 2;
            if(this.m_textCtn[_loc3_].IsArabic() == false)
            {
               this.m_iconCtn[_loc3_].x = _loc5_;
               this.m_textCtn[_loc3_].SetTextPos(this.m_iconCtn[_loc3_].x + this.m_iconCtn[_loc3_].width / 2 + this.CCD_TEXT_ICON_MARGIN,_loc4_ + this.CCD_LIST_LEADER * _loc3_ + _loc7_ + _loc14_);
            }
            else
            {
               this.m_textCtn[_loc3_].SetTextPos(45,_loc4_ + this.CCD_LIST_LEADER * _loc3_ + _loc7_ + _loc14_);
               this.m_iconCtn[_loc3_].x = 0;
            }
            _loc7_ += this.m_textCtn[_loc3_].GetSymbolHeight() / 2;
            _loc3_++;
         }
      }
   }
}

