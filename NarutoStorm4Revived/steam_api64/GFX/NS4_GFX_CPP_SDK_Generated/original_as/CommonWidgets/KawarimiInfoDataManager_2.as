package script.infoData
{
   public class KawarimiInfoDataManager extends InfoDataManagerBase
   {
      
      public function KawarimiInfoDataManager(param1:Array)
      {
         var _loc4_:InfoDataBase = null;
         super();
         var _loc2_:int = int(param1.length);
         m_dataList = new Array(_loc2_);
         var _loc3_:int = 0;
         while(_loc3_ < _loc2_)
         {
            m_dataList[_loc3_] = new KawarimiInfoData(param1[_loc3_]);
            _loc4_ = m_dataList[_loc3_];
            if(_loc4_.m_isNew)
            {
               m_newIconCheckItemKeyList.push(_loc4_.m_saveIdx);
            }
            _loc3_++;
         }
      }
      
      public function GetDataNum() : int
      {
         return m_dataList.length;
      }
      
      public function GetData(param1:int) : KawarimiInfoData
      {
         var _loc2_:KawarimiInfoData = null;
         if(param1 >= 0 && param1 < m_dataList.length)
         {
            _loc2_ = m_dataList[param1];
         }
         return _loc2_;
      }
   }
}

